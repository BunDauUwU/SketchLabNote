import { randomUUID } from "node:crypto";
import { pathToFileURL } from "node:url";
import { WebSocket, WebSocketServer } from "ws";

const DEFAULT_HOST = "127.0.0.1";
const DEFAULT_PORT = 14095;

function envelope(type, payload = {}) {
  return { type, payload };
}

export class LumieServer {
  constructor({ host = DEFAULT_HOST, port = DEFAULT_PORT } = {}) {
    this.host = host;
    this.port = port;
    this.clients = new Map();
    this.queues = new Map();
    this.matches = new Map();
    this.webSocketServer = null;
  }

  async start() {
    if (this.webSocketServer) return this.address();

    const server = new WebSocketServer({ host: this.host, port: this.port });
    this.webSocketServer = server;
    server.on("connection", (socket) => this.onConnection(socket));

    await new Promise((resolve, reject) => {
      server.once("listening", resolve);
      server.once("error", reject);
    });
    return this.address();
  }

  async stop() {
    if (!this.webSocketServer) return;
    const server = this.webSocketServer;
    this.webSocketServer = null;
    for (const socket of this.clients.keys()) socket.close();
    await new Promise((resolve) => server.close(resolve));
    this.clients.clear();
    this.queues.clear();
    this.matches.clear();
  }

  address() {
    const address = this.webSocketServer?.address();
    return typeof address === "object" && address ? address : null;
  }

  onConnection(socket) {
    this.clients.set(socket, {
      id: randomUUID(),
      nickname: "",
      deck: null,
      matchId: "",
    });

    socket.on("message", (raw, isBinary) => {
      if (isBinary) {
        this.sendError(socket, "InvalidMessage", "Binary messages are not supported");
        return;
      }
      this.onMessage(socket, raw.toString());
    });
    socket.on("close", () => this.onClose(socket));
    socket.on("error", () => {});
  }

  onMessage(socket, raw) {
    let message;
    try {
      message = JSON.parse(raw);
    } catch {
      this.sendError(socket, "InvalidJson", "Message must be valid JSON");
      return;
    }

    if (!message || typeof message !== "object" || Array.isArray(message) ||
        typeof message.type !== "string" || !message.payload ||
        typeof message.payload !== "object" || Array.isArray(message.payload)) {
      this.sendError(socket, "InvalidEnvelope", "Expected a type string and payload object");
      return;
    }

    const handlers = {
      AuthRequest: () => this.authenticate(socket, message.payload),
      SubmitDeck: () => this.submitDeck(socket, message.payload),
      MatchmakingStart: () => this.startMatchmaking(socket, message.payload),
      MatchmakingCancel: () => this.cancelMatchmaking(socket),
      GameCommand: () => this.gameCommand(socket, message.payload),
    };
    const handler = handlers[message.type];
    if (!handler) {
      this.sendError(socket, "UnknownMessageType", `Unsupported message type: ${message.type}`);
      return;
    }
    handler();
  }

  authenticate(socket, payload) {
    const nickname = typeof payload.nickname === "string" ? payload.nickname.trim() : "";
    if (!nickname || nickname.length > 32) {
      this.send(socket, "AuthResult", { success: false, message: "Nickname must contain 1 to 32 characters" });
      return;
    }
    const client = this.clients.get(socket);
    client.nickname = nickname;
    this.send(socket, "AuthResult", { success: true, playerId: client.id, nickname });
  }

  submitDeck(socket, payload) {
    const characters = payload.characters;
    const cards = payload.cards;
    if (!Array.isArray(characters) || !Array.isArray(cards) ||
        !characters.every((id) => typeof id === "string") ||
        !cards.every((id) => typeof id === "string")) {
      this.send(socket, "DeckValidationResult", {
        valid: false,
        message: "characters and cards must be arrays of IDs",
      });
      return;
    }
    this.clients.get(socket).deck = { deckId: String(payload.deckId ?? ""), characters, cards };
    this.send(socket, "DeckValidationResult", { valid: true, deckId: String(payload.deckId ?? "") });
  }

  startMatchmaking(socket, payload) {
    const client = this.clients.get(socket);
    if (!client.nickname) {
      this.sendError(socket, "NotAuthenticated", "Authenticate before starting matchmaking");
      return;
    }
    if (client.matchId) {
      this.sendError(socket, "AlreadyInMatch", "Client is already in a match");
      return;
    }

    this.removeFromQueues(socket);
    const mode = typeof payload.mode === "string" && payload.mode.trim() ? payload.mode.trim() : "Game1";
    const queue = this.queues.get(mode) ?? [];
    queue.push(socket);
    this.queues.set(mode, queue);
    this.send(socket, "MatchmakingStatus", { status: "Finding opponent...", mode });
    this.tryCreateMatch(mode);
  }

  cancelMatchmaking(socket) {
    this.removeFromQueues(socket);
    this.send(socket, "MatchmakingStatus", { status: "Matchmaking cancelled" });
  }

  tryCreateMatch(mode) {
    const queue = this.queues.get(mode) ?? [];
    while (queue.length >= 2) {
      const sockets = [queue.shift(), queue.shift()];
      if (sockets.some((socket) => socket.readyState !== WebSocket.OPEN)) continue;
      const matchId = randomUUID();
      const match = { id: matchId, mode, sockets, round: 1, currentPlayerIndex: 0, ended: new Set() };
      this.matches.set(matchId, match);

      sockets.forEach((socket, playerIndex) => {
        const client = this.clients.get(socket);
        const opponent = this.clients.get(sockets[1 - playerIndex]);
        client.matchId = matchId;
        this.send(socket, "MatchFound", { matchId, playerIndex, opponentName: opponent.nickname });
      });
      sockets.forEach((socket) => this.sendSnapshot(socket, match));
    }
    if (queue.length === 0) this.queues.delete(mode);
  }

  gameCommand(socket, payload) {
    const client = this.clients.get(socket);
    const match = this.matches.get(payload.matchId);
    if (!match || client.matchId !== payload.matchId || !match.sockets.includes(socket)) {
      this.sendError(socket, "MatchNotFound", "The requested match is not active");
      return;
    }
    const commandType = payload.commandType;
    if (typeof commandType !== "string" || !["ChooseActiveCharacter", "RedrawCards", "UseSkill", "PlayCard", "SwitchCharacter", "EndRound", "Concede"].includes(commandType)) {
      this.sendError(socket, "InvalidCommand", "Unknown game command");
      return;
    }

    const playerIndex = match.sockets.indexOf(socket);
    if (commandType === "Concede") {
      this.broadcast(match, "GameEvent", { matchId: match.id, events: [{ eventType: "GameEnded", reason: `${client.nickname} conceded` }] });
      this.finishMatch(match);
      return;
    }
    if (commandType === "EndRound") {
      match.ended.add(playerIndex);
      if (match.ended.size === 2) {
        match.round += 1;
        match.ended.clear();
        match.currentPlayerIndex = 1 - match.currentPlayerIndex;
      }
    }
    this.broadcast(match, "GameEvent", {
      matchId: match.id,
      events: [{ eventType: this.eventType(commandType), playerIndex, ...(payload.command ?? {}) }],
    });
    match.sockets.forEach((peer) => this.sendSnapshot(peer, match));
  }

  eventType(commandType) {
    return ({ ChooseActiveCharacter: "ActiveCharacterChanged", UseSkill: "SkillUsed", PlayCard: "CardPlayed", EndRound: "RoundEnded" })[commandType] ?? "StageChanged";
  }

  sendSnapshot(socket, match) {
    const localIndex = match.sockets.indexOf(socket);
    this.send(socket, "GameSnapshot", {
      matchId: match.id,
      stage: "Action",
      round: match.round,
      currentPlayerIndex: match.currentPlayerIndex,
      weather: { sequence: [], activeWeather: { type: "None", startedRound: 0, remainingRounds: 0 }, roundsPerWeather: 2 },
      players: match.sockets.map((peer) => {
        const player = this.clients.get(peer);
        return {
          playerId: player.id,
          nickname: player.nickname,
          characters: (player.deck?.characters ?? []).map((characterId, index) => ({ characterId, hp: 10, maxHp: 10, energy: 0, maxEnergy: 2, element: "None", active: index === 0, defeated: false })),
          elementPoints: { current: 10, maximum: 10, permanentBonus: 0 },
          handCardCount: 0,
          deckCardCount: player.deck?.cards.length ?? 0,
          activeCharacterIndex: 0,
        };
      }),
      self: { handCardIds: localIndex >= 0 ? [] : [] },
    });
  }

  onClose(socket) {
    this.removeFromQueues(socket);
    const client = this.clients.get(socket);
    const match = client?.matchId ? this.matches.get(client.matchId) : null;
    if (match) {
      const opponent = match.sockets.find((peer) => peer !== socket);
      this.send(opponent, "GameEvent", { matchId: match.id, events: [{ eventType: "GameEnded", reason: "Opponent disconnected" }] });
      this.finishMatch(match);
    }
    this.clients.delete(socket);
  }

  finishMatch(match) {
    this.matches.delete(match.id);
    for (const socket of match.sockets) {
      const client = this.clients.get(socket);
      if (client) client.matchId = "";
    }
  }

  removeFromQueues(socket) {
    for (const [mode, queue] of this.queues) {
      const filtered = queue.filter((candidate) => candidate !== socket);
      if (filtered.length) this.queues.set(mode, filtered);
      else this.queues.delete(mode);
    }
  }

  broadcast(match, type, payload) {
    match.sockets.forEach((socket) => this.send(socket, type, payload));
  }

  sendError(socket, code, message) {
    this.send(socket, "Error", { code, message });
  }

  send(socket, type, payload) {
    if (socket?.readyState === WebSocket.OPEN) socket.send(JSON.stringify(envelope(type, payload)));
  }
}

const isEntryPoint = process.argv[1] && import.meta.url === pathToFileURL(process.argv[1]).href;
if (isEntryPoint) {
  const server = new LumieServer({
    host: process.env.HOST ?? DEFAULT_HOST,
    port: Number.parseInt(process.env.PORT ?? String(DEFAULT_PORT), 10),
  });
  server.start().then((address) => {
    console.log(`LumieTCG server listening on ws://${address.address}:${address.port}`);
  }).catch((error) => {
    console.error("Unable to start LumieTCG server:", error);
    process.exitCode = 1;
  });
}
