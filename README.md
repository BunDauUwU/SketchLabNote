# LumieTCG

LumieTCG is a desktop trading card game inspired by Genshin Impact’s Genius Invokation TCG, built with **C++ and Qt 6 / QML**. It combines character-based battles and deck building with a custom Elemental Point resource system.

## Gameplay

Instead of rolling elemental dice, players start each round with **10 Elemental Points** to spend on actions. Cards and effects can modify these resources.

- Battle decks contain **3 unique characters and 30 cards**, with up to **3 copies** of each card.
- Characters, skills, equipment, support cards, states, and summons are described in JSON.
- The battle interface displays HP, Energy, Elemental Points, timers, weather, and action previews using server snapshots.

See [Battle rules and editable data](docs/battle-rules.md) for detailed mechanics and controls. Its server implementation and test references require the separate backend source.

## Current scope

This repository contains the Qt client, game data, and visual assets. It includes local account and deck persistence through SQLite, a deck builder, and WebSocket integration for matchmaking and battles.

Online battles require a compatible server. The backend source is **not included in this checkout**. Local persistence does not imply a complete offline battle mode.

## Build and run

### Requirements

- A C++ compiler supported by your Qt installation
- CMake 3.16 or newer
- Qt 6.2 or newer, including Qt Quick, QML, Qt Quick Controls, Qt SQL, and Qt WebSockets
- The Qt SQLite driver for local storage
- Ninja when using the commands below

Linux is the current development platform. You can open `CMakeLists.txt` in Qt Creator, select a desktop Qt kit, and build and run the `applumieTcg` target.

Alternatively, from the repository root:

```bash
cmake -S . -B build-local -G Ninja -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64
cmake --build build-local
./build-local/applumieTcg
```

Replace the Qt path with your installation directory. Omit `CMAKE_PREFIX_PATH` if CMake already finds Qt.

### Server connection

The client currently defaults to `wss://lumietcgserver.onrender.com/ws`. Override it without rebuilding by setting `LUMIETCG_SERVER_URL`:

```bash
LUMIETCG_SERVER_URL=ws://127.0.0.1:14095 ./build-local/applumieTcg
```

This local example requires a compatible backend listening on port `14095`. In Qt Creator, set the variable in the project’s Run Environment. Use `ws://` or `wss://` URLs. Startup and the reconnect button use the configured endpoint.

The client exchanges JSON messages with `type` and `payload` fields. It sends player actions and displays server snapshots; the server is responsible for validating online battle actions and resolving game state.

## Project structure

```text
lumieTcg/
├── assets/           # Images and visual resources
├── json/             # Cards, characters, states, and summons
├── qml/
│   ├── Components/   # Reusable UI and battle components
│   ├── Core/         # Theme, shared UI helpers, and scene management
│   └── Screens/      # Application screens
├── src/
│   ├── Core/         # Shared types, events, and snapshots
│   ├── Data/         # Game databases and asset resolution
│   ├── Managers/     # Accounts, decks, game flow, and matchmaking
│   ├── Models/       # Data exposed to the UI
│   └── Network/      # WebSocket transport and protocol
├── docs/             # Gameplay documentation
├── App.cpp           # Application entry point
└── CMakeLists.txt    # Qt application build configuration
```

C++ handles client data, persistence, networking, and application state. QML handles presentation, interaction, and animation. Navigation uses the existing `SceneManager` and `StackView`.

Game content uses stable IDs rather than image paths. The JSON files are embedded as Qt resources, so rebuild the client after changing them. Keep client data compatible with the backend used for online play.

## Development guidelines

- Preserve the existing directory structure, Qt/QML stack, CMake build, and scene navigation unless a change is explicitly requested.
- Extend existing classes incrementally and update affected callers when changing public APIs.
- Keep core game rules out of QML and keep online battle validation authoritative on the server.
- Preserve local account and deck storage unless a migration is explicitly requested.
- Add new systems only when needed for the requested feature.

## AI usage

AI was used to assist with:

- Writing JSON game data.
- Simplifying the project structure based on the original idea.
- Writing documentation.
