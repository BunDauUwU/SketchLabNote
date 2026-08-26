// src/Data/AssetResolver.cpp
#include "AssetResolver.h"
#include <QFileInfo>

AssetResolver::AssetResolver(QObject* parent) : QObject(parent)
{
}

QString AssetResolver::resolveCardImage(const QString& cardId)
{
    if (cardId.isEmpty()) return QStringLiteral("qrc:/assets/cards/Paimon.png");
    return QStringLiteral("qrc:/assets/cards/%1.png").arg(cardId);
}

QString AssetResolver::resolveCharacterImage(const QString& charId)
{
    if (charId.isEmpty()) return QStringLiteral("qrc:/assets/characters/Diluc.png");
    return QStringLiteral("qrc:/assets/characters/%1.png").arg(charId);
}

QString AssetResolver::resolveElementIcon(ElementType element)
{
    switch (element) {
    case ElementType::Anemo:   return QStringLiteral("qrc:/assets/elements/anemo.png");
    case ElementType::Cryo:    return QStringLiteral("qrc:/assets/elements/cryo.png");
    case ElementType::Dendro:  return QStringLiteral("qrc:/assets/elements/dendro.png");
    case ElementType::Electro: return QStringLiteral("qrc:/assets/elements/electro.png");
    case ElementType::Geo:     return QStringLiteral("qrc:/assets/elements/geo.png");
    case ElementType::Hydro:   return QStringLiteral("qrc:/assets/elements/hydro.png");
    case ElementType::Pyro:    return QStringLiteral("qrc:/assets/elements/pyro.png");
    case ElementType::Omni:    return QStringLiteral("qrc:/assets/elements/omni.png");
    default:                   return QStringLiteral("qrc:/assets/costs/ANY.png");
    }
}

QString AssetResolver::resolveWeatherIcon(WeatherType weather)
{
    switch (weather) {
    case WeatherType::Rain:         return QStringLiteral("☔");
    case WeatherType::Snow:         return QStringLiteral("❄");
    case WeatherType::Thunderstorm: return QStringLiteral("⚡");
    case WeatherType::Sandstorm:    return QStringLiteral("🌪");
    case WeatherType::Cataclysm:    return QStringLiteral("☄");
    case WeatherType::BurningField: return QStringLiteral("🔥");
    case WeatherType::Tornado:      return QStringLiteral("🌪");
    default:                        return QStringLiteral("☀️");
    }
}

QString AssetResolver::resolveWeatherName(WeatherType weather)
{
    switch (weather) {
    case WeatherType::Rain:         return QStringLiteral("Rainstorm");
    case WeatherType::Snow:         return QStringLiteral("Blizzard");
    case WeatherType::Thunderstorm: return QStringLiteral("Thunderstorm");
    case WeatherType::Sandstorm:    return QStringLiteral("Sandstorm");
    case WeatherType::Cataclysm:    return QStringLiteral("Cataclysm");
    case WeatherType::BurningField: return QStringLiteral("Burning Field");
    case WeatherType::Tornado:      return QStringLiteral("Tornado");
    default:                        return QStringLiteral("Clear Sky");
    }
}

QString AssetResolver::resolveWeatherDescription(WeatherType weather)
{
    switch (weather) {
    case WeatherType::Rain:
        return QStringLiteral("All characters gain a Hydro application at round start.");
    case WeatherType::Snow:
        return QStringLiteral("All characters gain a Cryo application at round start.");
    case WeatherType::Thunderstorm:
        return QStringLiteral("One random character on each team gains Electro and loses 1 HP.");
    case WeatherType::Sandstorm:
        return QStringLiteral("Characters cannot attack during this round.");
    case WeatherType::Cataclysm:
        return QStringLiteral("Elemental reactions are disabled and all applications are removed.");
    case WeatherType::BurningField:
        return QStringLiteral("Summons disappear and a random character on each team gains Pyro.");
    case WeatherType::Tornado:
        return QStringLiteral("Hands return to their decks, then each player draws three cards.");
    default:
        return QStringLiteral("Standard battlefield conditions.");
    }
}
