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
    case WeatherType::Storm:        return QStringLiteral("⚡");
    case WeatherType::Sandstorm:    return QStringLiteral("🌪");
    case WeatherType::Eclipse:      return QStringLiteral("🌒");
    case WeatherType::BurningField: return QStringLiteral("🔥");
    default:                        return QStringLiteral("☀️");
    }
}

QString AssetResolver::resolveWeatherName(WeatherType weather)
{
    switch (weather) {
    case WeatherType::Rain:         return QStringLiteral("Rainstorm");
    case WeatherType::Snow:         return QStringLiteral("Blizzard");
    case WeatherType::Storm:        return QStringLiteral("Thunderstorm");
    case WeatherType::Sandstorm:    return QStringLiteral("Sandstorm");
    case WeatherType::Eclipse:      return QStringLiteral("Solar Eclipse");
    case WeatherType::BurningField: return QStringLiteral("Burning Field");
    default:                        return QStringLiteral("Clear Sky");
    }
}

QString AssetResolver::resolveWeatherDescription(WeatherType weather)
{
    switch (weather) {
    case WeatherType::Rain:
        return QStringLiteral("Hydro reactions are amplified. Water costs are reduced by 1 EP.");
    case WeatherType::Snow:
        return QStringLiteral("Cryo damage freezes enemies for 1 turn. Physical damage is reduced.");
    case WeatherType::Storm:
        return QStringLiteral("Electro charges quickly. Gain +1 Energy at round start.");
    case WeatherType::Sandstorm:
        return QStringLiteral("Geo shields gain +2 absorption. Non-Geo skills cost +1 EP.");
    case WeatherType::Eclipse:
        return QStringLiteral("Darkness engulfs the field. Ultimate skill damage increased by +3.");
    case WeatherType::BurningField:
        return QStringLiteral("Pyro damage inflicts Burning status. End-of-turn damage to all active characters.");
    default:
        return QStringLiteral("Standard battlefield conditions.");
    }
}
