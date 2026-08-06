// src/Core/GameSnapshot.h
#pragma once

#include <QString>
#include <QVector>

#include "Enums.h"
#include "GameTypes.h"

struct ElementPointPool {
    int current = GameRules::startingElementPoints;
    int maximum = GameRules::defaultMaximumElementPoints;
    int permanentBonus = 0;

    [[nodiscard]] int availableCapacity() const
    {
        return GameRules::clampElementPoints(maximum - current, maximum);
    }

    [[nodiscard]] bool canSpend(int amount) const
    {
        return amount >= 0 && current >= amount;
    }
};

struct WeatherState {
    WeatherType type = WeatherType::None;
    int startedRound = 0;
    int remainingRounds = 0;
};

struct MatchWeatherPlan {
    QVector<WeatherType> sequence;
    WeatherState activeWeather;
    int roundsPerWeather = GameRules::roundsPerWeather;
};

struct CharacterState {
    QString characterId;
    int hp = 10;
    int maxHp = 10;
    int energy = 0;
    int maxEnergy = 2;
    ElementType element = ElementType::None;
    bool active = false;
    bool defeated = false;
};

struct PlayerPublicState {
    QString playerId;
    QString nickname;
    QVector<CharacterState> characters;
    ElementPointPool elementPoints;
    int handCardCount = 0;
    int deckCardCount = 0;
    int activeCharacterIndex = -1;
};

struct PlayerPrivateState {
    QVector<QString> handCardIds;
};

struct GameSnapshot {
    QString matchId;
    GameStage stage = GameStage::None;
    int round = 0;
    int currentPlayerIndex = -1;
    MatchWeatherPlan weather;
    QVector<PlayerPublicState> players;
    PlayerPrivateState self;
};
