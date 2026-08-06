// src/Core/EnumUtils.cpp
#include "EnumUtils.h"

namespace {

QString normalize(const QString& value)
{
    return value.trimmed().toLower();
}

}

namespace EnumUtils {

QString toString(ElementType type)
{
    switch (type) {
    case ElementType::None: return QStringLiteral("None");
    case ElementType::Omni: return QStringLiteral("Omni");
    case ElementType::Cryo: return QStringLiteral("Cryo");
    case ElementType::Hydro: return QStringLiteral("Hydro");
    case ElementType::Pyro: return QStringLiteral("Pyro");
    case ElementType::Electro: return QStringLiteral("Electro");
    case ElementType::Geo: return QStringLiteral("Geo");
    case ElementType::Dendro: return QStringLiteral("Dendro");
    case ElementType::Anemo: return QStringLiteral("Anemo");
    }

    return QStringLiteral("None");
}

ElementType elementTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "omni") return ElementType::Omni;
    if (v == "cryo") return ElementType::Cryo;
    if (v == "hydro") return ElementType::Hydro;
    if (v == "pyro") return ElementType::Pyro;
    if (v == "electro") return ElementType::Electro;
    if (v == "geo") return ElementType::Geo;
    if (v == "dendro") return ElementType::Dendro;
    if (v == "anemo") return ElementType::Anemo;

    return ElementType::None;
}

QString toString(WeatherType type)
{
    switch (type) {
    case WeatherType::None: return QStringLiteral("None");
    case WeatherType::Rain: return QStringLiteral("Rain");
    case WeatherType::Snow: return QStringLiteral("Snow");
    case WeatherType::Storm: return QStringLiteral("Storm");
    case WeatherType::Sandstorm: return QStringLiteral("Sandstorm");
    case WeatherType::Eclipse: return QStringLiteral("Eclipse");
    case WeatherType::BurningField: return QStringLiteral("BurningField");
    }

    return QStringLiteral("None");
}

WeatherType weatherTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "rain") return WeatherType::Rain;
    if (v == "snow") return WeatherType::Snow;
    if (v == "storm") return WeatherType::Storm;
    if (v == "sandstorm") return WeatherType::Sandstorm;
    if (v == "eclipse") return WeatherType::Eclipse;
    if (v == "burningfield" || v == "burning_field" || v == "burning field") return WeatherType::BurningField;

    return WeatherType::None;
}

QString toString(GameStage stage)
{
    switch (stage) {
    case GameStage::None: return QStringLiteral("None");
    case GameStage::GameStart: return QStringLiteral("GameStart");
    case GameStage::RoundStart: return QStringLiteral("RoundStart");
    case GameStage::Roll: return QStringLiteral("Roll");
    case GameStage::Action: return QStringLiteral("Action");
    case GameStage::RoundEnd: return QStringLiteral("RoundEnd");
    case GameStage::GameEnd: return QStringLiteral("GameEnd");
    }

    return QStringLiteral("None");
}

GameStage gameStageFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "gamestart") return GameStage::GameStart;
    if (v == "roundstart") return GameStage::RoundStart;
    if (v == "roll") return GameStage::Roll;
    if (v == "action") return GameStage::Action;
    if (v == "roundend") return GameStage::RoundEnd;
    if (v == "gameend") return GameStage::GameEnd;

    return GameStage::None;
}

QString toString(CardType type)
{
    switch (type) {
    case CardType::Any: return QStringLiteral("Any");
    case CardType::Talent: return QStringLiteral("Talent");
    case CardType::Weapon: return QStringLiteral("Weapon");
    case CardType::ElementalResonance: return QStringLiteral("ElementalResonance");
    case CardType::Food: return QStringLiteral("Food");
    case CardType::Event: return QStringLiteral("Event");
    case CardType::Artifact: return QStringLiteral("Artifact");
    }

    return QStringLiteral("Any");
}

CardType cardTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "talent") return CardType::Talent;
    if (v == "weapon") return CardType::Weapon;
    if (v == "elementalresonance") return CardType::ElementalResonance;
    if (v == "food") return CardType::Food;
    if (v == "event") return CardType::Event;
    if (v == "artifact") return CardType::Artifact;

    return CardType::Any;
}

QString toString(NetworkMessageType type)
{
    switch (type) {
    case NetworkMessageType::Unknown: return QStringLiteral("Unknown");
    case NetworkMessageType::AuthRequest: return QStringLiteral("AuthRequest");
    case NetworkMessageType::AuthResult: return QStringLiteral("AuthResult");
    case NetworkMessageType::MatchmakingStart: return QStringLiteral("MatchmakingStart");
    case NetworkMessageType::MatchmakingCancel: return QStringLiteral("MatchmakingCancel");
    case NetworkMessageType::MatchFound: return QStringLiteral("MatchFound");
    case NetworkMessageType::MatchmakingStatus: return QStringLiteral("MatchmakingStatus");
    case NetworkMessageType::SubmitDeck: return QStringLiteral("SubmitDeck");
    case NetworkMessageType::DeckValidationResult: return QStringLiteral("DeckValidationResult");
    case NetworkMessageType::GameSnapshot: return QStringLiteral("GameSnapshot");
    case NetworkMessageType::GameCommand: return QStringLiteral("GameCommand");
    case NetworkMessageType::GameEvent: return QStringLiteral("GameEvent");
    case NetworkMessageType::Error: return QStringLiteral("Error");
    }

    return QStringLiteral("Unknown");
}

NetworkMessageType networkMessageTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "authrequest") return NetworkMessageType::AuthRequest;
    if (v == "authresult") return NetworkMessageType::AuthResult;
    if (v == "matchmakingstart") return NetworkMessageType::MatchmakingStart;
    if (v == "matchmakingcancel") return NetworkMessageType::MatchmakingCancel;
    if (v == "matchfound") return NetworkMessageType::MatchFound;
    if (v == "matchmakingstatus") return NetworkMessageType::MatchmakingStatus;
    if (v == "submitdeck") return NetworkMessageType::SubmitDeck;
    if (v == "deckvalidationresult") return NetworkMessageType::DeckValidationResult;
    if (v == "gamesnapshot") return NetworkMessageType::GameSnapshot;
    if (v == "gamecommand") return NetworkMessageType::GameCommand;
    if (v == "gameevent") return NetworkMessageType::GameEvent;
    if (v == "error") return NetworkMessageType::Error;

    return NetworkMessageType::Unknown;
}

QString toString(GameCommandType type)
{
    switch (type) {
    case GameCommandType::Unknown: return QStringLiteral("Unknown");
    case GameCommandType::ChooseActiveCharacter: return QStringLiteral("ChooseActiveCharacter");
    case GameCommandType::RedrawCards: return QStringLiteral("RedrawCards");
    case GameCommandType::UseSkill: return QStringLiteral("UseSkill");
    case GameCommandType::PlayCard: return QStringLiteral("PlayCard");
    case GameCommandType::SwitchCharacter: return QStringLiteral("SwitchCharacter");
    case GameCommandType::EndRound: return QStringLiteral("EndRound");
    case GameCommandType::Concede: return QStringLiteral("Concede");
    }

    return QStringLiteral("Unknown");
}

GameCommandType gameCommandTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "chooseactivecharacter") return GameCommandType::ChooseActiveCharacter;
    if (v == "redrawcards") return GameCommandType::RedrawCards;
    if (v == "useskill") return GameCommandType::UseSkill;
    if (v == "playcard") return GameCommandType::PlayCard;
    if (v == "switchcharacter") return GameCommandType::SwitchCharacter;
    if (v == "endround") return GameCommandType::EndRound;
    if (v == "concede") return GameCommandType::Concede;

    return GameCommandType::Unknown;
}

QString toString(GameEventType type)
{
    switch (type) {
    case GameEventType::Unknown: return QStringLiteral("Unknown");
    case GameEventType::GameStarted: return QStringLiteral("GameStarted");
    case GameEventType::RoundStarted: return QStringLiteral("RoundStarted");
    case GameEventType::StageChanged: return QStringLiteral("StageChanged");
    case GameEventType::CardsDrawn: return QStringLiteral("CardsDrawn");
    case GameEventType::ElementPointsChanged: return QStringLiteral("ElementPointsChanged");
    case GameEventType::WeatherChanged: return QStringLiteral("WeatherChanged");
    case GameEventType::CharacterDamaged: return QStringLiteral("CharacterDamaged");
    case GameEventType::CharacterHealed: return QStringLiteral("CharacterHealed");
    case GameEventType::EnergyChanged: return QStringLiteral("EnergyChanged");
    case GameEventType::ActiveCharacterChanged: return QStringLiteral("ActiveCharacterChanged");
    case GameEventType::CardPlayed: return QStringLiteral("CardPlayed");
    case GameEventType::SkillUsed: return QStringLiteral("SkillUsed");
    case GameEventType::SummonCreated: return QStringLiteral("SummonCreated");
    case GameEventType::SupportCreated: return QStringLiteral("SupportCreated");
    case GameEventType::StateAttached: return QStringLiteral("StateAttached");
    case GameEventType::RoundEnded: return QStringLiteral("RoundEnded");
    case GameEventType::GameEnded: return QStringLiteral("GameEnded");
    }

    return QStringLiteral("Unknown");
}

GameEventType gameEventTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "gamestarted") return GameEventType::GameStarted;
    if (v == "roundstarted") return GameEventType::RoundStarted;
    if (v == "stagechanged") return GameEventType::StageChanged;
    if (v == "cardsdrawn") return GameEventType::CardsDrawn;
    if (v == "elementpointschanged") return GameEventType::ElementPointsChanged;
    if (v == "weatherchanged") return GameEventType::WeatherChanged;
    if (v == "characterdamaged") return GameEventType::CharacterDamaged;
    if (v == "characterhealed") return GameEventType::CharacterHealed;
    if (v == "energychanged") return GameEventType::EnergyChanged;
    if (v == "activecharacterchanged") return GameEventType::ActiveCharacterChanged;
    if (v == "cardplayed") return GameEventType::CardPlayed;
    if (v == "skillused") return GameEventType::SkillUsed;
    if (v == "summoncreated") return GameEventType::SummonCreated;
    if (v == "supportcreated") return GameEventType::SupportCreated;
    if (v == "stateattached") return GameEventType::StateAttached;
    if (v == "roundended") return GameEventType::RoundEnded;
    if (v == "gameended") return GameEventType::GameEnded;

    return GameEventType::Unknown;
}

QString toString(ZoneType type)
{
    switch (type) {
    case ZoneType::None: return QStringLiteral("None");
    case ZoneType::Deck: return QStringLiteral("Deck");
    case ZoneType::Hand: return QStringLiteral("Hand");
    case ZoneType::Character: return QStringLiteral("Character");
    case ZoneType::Support: return QStringLiteral("Support");
    case ZoneType::Summon: return QStringLiteral("Summon");
    case ZoneType::Discard: return QStringLiteral("Discard");
    }

    return QStringLiteral("None");
}

ZoneType zoneTypeFromString(const QString& value)
{
    const QString v = normalize(value);

    if (v == "deck") return ZoneType::Deck;
    if (v == "hand") return ZoneType::Hand;
    if (v == "character") return ZoneType::Character;
    if (v == "support") return ZoneType::Support;
    if (v == "summon") return ZoneType::Summon;
    if (v == "discard") return ZoneType::Discard;

    return ZoneType::None;
}

}
