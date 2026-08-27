// src/Core/Enums.h
#pragma once

#include <QString>

enum class ElementType {
    None = -1,
    Omni = 0,
    Cryo,
    Hydro,
    Pyro,
    Electro,
    Geo,
    Dendro,
    Anemo
};

enum class WeatherType {
    None,
    Rain,
    Snow,
    Thunderstorm,
    Sandstorm,
    Cataclysm,
    BurningField,
    Tornado
};

enum class GameStage {
    None,
    GameStart,
    RoundStart,
    Roll,
    Action,
    RoundEnd,
    GameEnd
};

enum class CardType {
    Any,
    Talent,
    Weapon,
    ElementalResonance,
    Food,
    Event,
    Artifact
};

enum class NetworkMessageType {
    Unknown,
    AuthRequest,
    AuthResult,
    MatchmakingStart,
    MatchmakingCancel,
    MatchFound,
    MatchmakingStatus,
    SubmitDeck,
    DeckValidationResult,
    GameSnapshot,
    GameCommand,
    GameEvent,
    Error
};

enum class GameCommandType {
    Unknown,
    ChooseActiveCharacter,
    RedrawCards,
    UseSkill,
    PlayCard,
    SwitchCharacter,
    EndRound,
    Concede
};

enum class GameEventType {
    Unknown,
    GameStarted,
    RoundStarted,
    StageChanged,
    CardsDrawn,
    ElementPointsChanged,
    WeatherChanged,
    CharacterDamaged,
    CharacterHealed,
    EnergyChanged,
    ActiveCharacterChanged,
    CardPlayed,
    SkillUsed,
    SummonCreated,
    SupportCreated,
    StateAttached,
    RoundEnded,
    GameEnded
};

enum class ZoneType {
    None,
    Deck,
    Hand,
    Character,
    Support,
    Summon,
    Discard
};
