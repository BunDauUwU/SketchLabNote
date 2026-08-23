# LumieTCG

A Genshin-inspired online-capable Trading Card Game built with **C++ / Qt 6 / QML**.

The project focuses on creating a polished card-game experience inspired by Genshin Impact's Genius Invokation TCG, while introducing a different core resource system and future gameplay modifiers.

---

# 1. Product Vision

LumieTCG is a strategic TCG with:

- Genshin-inspired characters, cards, skills and visual style
- Turn-based card battles
- Character-based combat
- Support, equipment and other card types
- A deck-building system
- Player accounts
- Local persistence first
- Online multiplayer in the future

The long-term goal is to evolve the project into a fully online multiplayer TCG.

However, the current development stage is **local-first**.

Do NOT implement the online backend prematurely unless explicitly requested.

---

# 2. Core Gameplay Direction

LumieTCG is inspired by Genshin Impact's Genius Invokation TCG, but it is NOT intended to copy its rules exactly.

## Elemental Point System

The traditional dice system is removed.

Each player starts each round with:

    10 Elemental Points

Players can spend Elemental Points to perform actions.

Players may gain additional Elemental Points through specific support cards or effects.

Examples:

- Lose 2 points every round → gain 2 points later
- Sacrifice HP from a card/character → gain Elemental Points
- Other future card effects may modify Elemental Points

The Elemental Point system is intended to become one of the main strategic resources of the game.

---

# 3. Future Weather System

Weather is a planned gameplay system.

It does NOT need to be fully implemented yet.

The intended design:

- Each match randomly selects 3 weather conditions.
- Weather changes every 2 rounds.
- Each weather condition provides a special gameplay effect.
- Weather exists as a future method of changing the metagame and encouraging different deck strategies.

Example future concepts:

- Pyro-related weather
- Cryo-related weather
- Healing-related weather
- Elemental cost modification
- Damage modification
- Energy modification

IMPORTANT:

Do not implement the complete weather system unless explicitly requested.

The system should eventually be designed so that adding new weather effects does not require rewriting the battle engine.

---

# 4. Technology

## Client

- C++
- Qt 6.x
- Qt Quick
- QML
- Qt Quick Controls
- Qt WebSockets

## Build System

- CMake
- Ninja

## IDE

- Qt Creator

## Current Platform

Linux / Desktop

The project should remain cross-platform where reasonably possible.

## Running the multiplayer server

The client connects to `ws://127.0.0.1:14095`. Start the compatible JavaScript
WebSocket server in a separate terminal before launching the client:

```bash
cd server
npm install
npm start
```

Set `HOST` or `PORT` to override the listening address. The server uses the same
JSON `{ "type", "payload" }` envelopes as the C++ `Protocol` implementation and
supports guest authentication, deck submission, matchmaking, game snapshots,
game commands, cancellation, and disconnect cleanup.

Battle decks must contain exactly 3 unique characters and 30 cards, with no
more than 3 copies of a card. After matchmaking, both players have 10 seconds
to select one of their three valid decks. The server then performs the initial
five-card draw, publishes the shuffled three-weather plan, applies round weather,
and enforces both the 30-second action timer and each player's game clock.

---

# 5. UI Architecture

The UI is built with QML.

C++ is responsible for:

- Game logic
- Data management
- Managers
- Networking
- Persistence
- Models
- Core systems

QML is responsible for:

- UI
- Visual presentation
- Animations
- Scene composition
- User interaction

Avoid moving game logic into QML when the logic belongs in C++.

---

# 6. Scene Management

The application uses a centralized Scene Manager based on QML `StackView`.

Conceptually:

    App
     |
     +-- SceneManager
            |
            +-- SplashScreen
            +-- MainMenu
            +-- BattleScreen
            +-- DeckScreen
            +-- CollectionScreen
            +-- SettingsScreen

Scenes should be pushed/replaced through the existing SceneManager/StackView architecture.

Do NOT create independent navigation systems for individual screens.

---

# 7. Project Structure

The current project structure is intentional and should NOT be changed without explicit approval.

    lumieTcg/
    │
    ├── assets/
    │
    ├── qml/
    │   ├── Components/
    │   │   ├── battle/
    │   │   ├── cards/
    │   │   ├── common/
    │   │   ├── controls/
    │   │   └── layout/
    │   │
    │   ├── Core/
    │   │
    │   └── Screens/
    │
    ├── src/
    │   ├── Core/
    │   ├── Data/
    │   ├── Managers/
    │   ├── Models/
    │   └── Network/
    │
    ├── App.cpp
    ├── CMakeLists.txt
    └── README.md

This structure is considered stable.

AI agents MUST NOT reorganize or rename these directories simply for convenience.

---

# 8. C++ Architecture

Important existing systems include:

## Core

Contains shared game types, enums, events and snapshots.

Examples:

- GameTypes
- GameEvent
- GameSnapshot
- Enums
- EnumUtils

---

## Data

Contains static game data.

Examples:

- CardDatabase
- CharacterDatabase
- AssetResolver

The Data layer should describe game content.

It should not become responsible for UI.

---

## Managers

Managers control high-level systems.

Important managers:

- AuthManager
- DeckManager
- GameManager
- MatchmakingManager
- AppManager
- AssetManager

Managers should expose clean APIs to QML when necessary.

---

## Models

Models represent data exposed to the UI/game systems.

Examples:

- CardModel
- CharacterModel
- PlayerModel
- BoardModel

---

## Network

Contains networking infrastructure.

Examples:

- NetworkClient
- Protocol
- MessageRouter
- RealtimeTransport

The network layer exists now because the project is intended to become online later.

However, online multiplayer is NOT the current priority.

---

# 9. Authentication

Authentication currently uses a local SQLite database.

Current concept:

    AuthManager
        |
        v
    users.sqlite
        |
        +-- users

The current implementation is intentionally local.

DO NOT replace the local authentication system with a server implementation unless explicitly requested.

The architecture should remain easy to migrate to online authentication later.

---

# 10. Deck System

Each player can have a maximum of:

    5 decks

Each deck can contain:

    Maximum 3 characters
    Maximum 30 cards

Deck data should contain:

- Deck ID
- Deck name
- Character IDs
- Card IDs

Example:

    Deck
    ├── id
    ├── name
    ├── characters[]
    └── cards[]

The DeckManager is responsible for:

- Creating decks
- Deleting decks
- Renaming decks
- Loading decks
- Saving decks
- Adding/removing characters
- Adding/removing cards
- Validating deck rules

---

# 11. Local Persistence

The current project is LOCAL-FIRST.

The current goal is to store user/account/deck information locally using SQLite.

Do NOT prematurely replace this with an online database.

The future migration should conceptually become:

    Current:

    QML
      |
      v
    Manager
      |
      v
    SQLite


    Future:

    QML
      |
      v
    Manager
      |
      v
    NetworkClient
      |
      v
    Server
      |
      v
    Database

The QML layer should ideally not need to know whether data is stored locally or remotely.

---

# 12. Online Multiplayer - FUTURE

Online multiplayer is a future goal.

The project already contains networking-related classes because the architecture is being prepared for this.

Future architecture:

    Client
       |
       | WebSocket
       v
    Game Server
       |
       +-- Authentication
       +-- Matchmaking
       +-- Deck validation
       +-- Game state
       +-- Battle rules
       +-- Player data
       |
       v
    Database

When online multiplayer is implemented, the server must be authoritative.

The client must NOT be trusted for:

- Card ownership
- Deck legality
- Damage calculation
- Resource validation
- Turn validation
- Game state
- Match results

The client should primarily display state and send player actions.

---

# 13. Card Data

Cards should be represented using stable IDs rather than hard-coded asset paths.

For example:

    "kamisato_ayaka"
    "jueyun_guoba"
    "paimon"

Asset paths are presentation details.

Game logic should operate on IDs/data rather than directly depending on image filenames.

---

# 14. Characters

Characters should eventually contain structured data such as:

- ID
- Name
- Element
- HP
- Skills
- Energy
- Statuses
- Talents
- Other gameplay properties

Character data should remain separated from UI.

---

# 15. Summons

Summons are gameplay entities.

A summon should eventually be represented by structured data rather than being treated only as an image.

Potential data:

- ID
- Duration
- Trigger condition
- Damage
- Element
- Effects
- Number of usages

The summon system should be extensible.

Do not hard-code every summon into unrelated battle/UI code.

---

# 16. Battle System

The battle system is one of the most important long-term systems.

The battle engine should eventually be independent from QML presentation.

Conceptually:

    Player Action
        |
        v
    GameManager / Battle Logic
        |
        v
    Validate Action
        |
        v
    Update Game State
        |
        v
    GameSnapshot
        |
        v
    QML
        |
        v
    Visual Update

QML should display the state rather than become the source of truth for game rules.

---

# 17. Development Priorities

Development should generally follow this order:

## Phase 1 - Foundation

- Stable project structure
- Scene Manager
- Main Menu
- Components
- Theme
- Resources
- Basic application flow

## Phase 2 - Data

- Card database
- Character database
- Card models
- Character models
- Asset management

## Phase 3 - Accounts

- Local registration
- Local login
- Logout
- Current user/session

## Phase 4 - Deck Builder

- Maximum 5 decks
- 3 characters per deck
- 30 cards per deck
- Add/remove cards
- Add/remove characters
- Save/load through SQLite

## Phase 5 - Battle Prototype

- Board
- Characters
- HP
- Energy
- Elemental Points
- Skills
- Basic turn system

## Phase 6 - Game Systems

- Status effects
- Summons
- Equipment
- Support cards
- Elemental reactions
- More advanced card interactions

## Phase 7 - Online

Only after the local game is stable:

- Server authentication
- Online deck synchronization
- Matchmaking
- Server-authoritative battle
- Realtime game state
- Reconnection
- Match results

---

# 18. Current Priority

The immediate priority is NOT:

- Full online multiplayer
- Weather
- Advanced matchmaking
- Production backend
- Anti-cheat
- Large-scale server infrastructure

The immediate priority is:

    Stable Client
        ↓
    Stable UI
        ↓
    Stable Data
        ↓
    Stable Deck System
        ↓
    Playable Local Battle
        ↓
    Online later

---

# 19. Rules for AI / Codex

AI agents working on this repository MUST follow these rules.

### Rule 1 - Do not change the project architecture

Do not:

- Move directories
- Rename directories
- Create a new architecture
- Replace Qt/QML
- Replace CMake
- Replace the SceneManager
- Replace StackView

unless explicitly instructed.

---

### Rule 2 - Prefer incremental changes

Before creating a new system:

1. Inspect the existing implementation.
2. Reuse existing classes.
3. Extend existing architecture.
4. Only create new files when necessary.

Do not rewrite working systems unnecessarily.

---

### Rule 3 - Preserve existing APIs

If an existing class is already used by QML or another C++ system, avoid breaking its public API.

If an API must change, update all affected callers.

---

### Rule 4 - Keep C++ and QML responsibilities separated

Use:

    C++ → logic/data/state

    QML → UI/presentation/animation

Do not implement core game rules inside QML simply because it is easier.

---

### Rule 5 - Do not implement future systems prematurely

Weather, online authentication, matchmaking and server infrastructure are future systems.

Do not introduce unnecessary complexity before the local game is playable.

---

### Rule 6 - Do not replace working code without reason

If a current implementation works, improve it incrementally.

Avoid large rewrites unless the existing design fundamentally prevents the required feature.

---

### Rule 7 - Always consider future online migration

Local-first does NOT mean designing a dead-end architecture.

Systems such as:

- AuthManager
- DeckManager
- GameManager
- NetworkClient

should have clear responsibilities so that local storage can later be replaced or supplemented by server communication.

---

# 20. Definition of Success

The project should eventually become:

- A polished Qt/QML TCG
- Visually inspired by Genshin
- Strategically different through its Elemental Point system
- Extensible through cards, characters, summons and future weather
- Playable locally
- Account-aware
- Deck-builder focused
- Architecturally ready for online multiplayer
- Server-authoritative when online

The most important principle is:

> Build a solid local game first, while keeping the architecture clean enough to become an online game later.
