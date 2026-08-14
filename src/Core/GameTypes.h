// src/Core/GameTypes.h
#pragma once
#include <QString>
#include <QStringList>

namespace GameRules {

inline constexpr int startingElementPoints = 10;
inline constexpr int defaultMaximumElementPoints = 10;
inline constexpr int minimumElementPoints = 0;
inline constexpr int weatherEffectsPerMatch = 3;
inline constexpr int roundsPerWeather = 2;

constexpr int clampElementPoints(int value, int maximum = defaultMaximumElementPoints)
{
    if (value < minimumElementPoints) {
        return minimumElementPoints;
    }

    if (value > maximum) {
        return maximum;
    }

    return value;
}
} // namespace GameRules

struct Deck
{
    QString id;
    QString name;

    QStringList characters;
    QStringList cards;
};
