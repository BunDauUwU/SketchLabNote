// src/Data/AssetResolver.cpp
#include "AssetResolver.h"
#include <QFileInfo>
#include <QDirIterator>
#include <QHash>
#include <QRegularExpression>

AssetResolver::AssetResolver(QObject* parent) : QObject(parent)
{
}

namespace {
QString normalized(QString value)
{
    value = QFileInfo(value).completeBaseName();
    value.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
    return value.toLower();
}

QString resolveImage(const QString& id, const QString& zone)
{
    // Database URLs, asset filenames and canonical server names share one lookup.
    static QHash<QString, QString> images;
    if (images.isEmpty()) {
        QDirIterator it(QStringLiteral(":"), QDirIterator::Subdirectories);
        while (it.hasNext()) {
            const QString path = it.next();
            const QFileInfo info(path);
            if (!info.isFile() || !QStringList{"png", "jpg", "jpeg"}.contains(info.suffix().toLower())) continue;
            for (const QString& folder : {QStringLiteral("cards"), QStringLiteral("characters"), QStringLiteral("elements"), QStringLiteral("summons"), QStringLiteral("states")}) {
                if (path.contains("/assets/" + folder + "/"))
                    images.insert(folder + "/" + normalized(info.fileName()), "qrc" + path);
            }
        }
    }
    return images.value(zone + "/" + normalized(id));
}
}

QString AssetResolver::resolveCardImage(const QString& cardId)
{
    return resolveImage(cardId, QStringLiteral("cards"));
}

QString AssetResolver::resolveCharacterImage(const QString& charId)
{
    return resolveImage(charId, QStringLiteral("characters"));
}

QString AssetResolver::resolveElementImage(const QString& element)
{
    return resolveImage(element, QStringLiteral("elements"));
}

QString AssetResolver::resolveEffectImage(const QString& name, const QString& kind, const QString& icon)
{
    const QString zone = kind == QStringLiteral("summon") ? QStringLiteral("summons") : QStringLiteral("states");
    QString image = resolveImage(name, zone);
    if (image.isEmpty() && !icon.isEmpty()) image = resolveImage(icon, zone);
    if (image.isEmpty()) image = resolveImage(QStringLiteral("state"), QStringLiteral("states"));
    return image;
}

QString AssetResolver::resolveElementIcon(ElementType element)
{
    switch (element) {
    case ElementType::Anemo:   return QStringLiteral("qrc:/lumieTcg/assets/elements/anemo.png");
    case ElementType::Cryo:    return QStringLiteral("qrc:/lumieTcg/assets/elements/cryo.png");
    case ElementType::Dendro:  return QStringLiteral("qrc:/lumieTcg/assets/elements/dendro.png");
    case ElementType::Electro: return QStringLiteral("qrc:/lumieTcg/assets/elements/electro.png");
    case ElementType::Geo:     return QStringLiteral("qrc:/lumieTcg/assets/elements/geo.png");
    case ElementType::Hydro:   return QStringLiteral("qrc:/lumieTcg/assets/elements/hydro.png");
    case ElementType::Pyro:    return QStringLiteral("qrc:/lumieTcg/assets/elements/pyro.png");
    case ElementType::Omni:    return QStringLiteral("qrc:/lumieTcg/assets/elements/omni.png");
    default:                   return QStringLiteral("qrc:/lumieTcg/assets/costs/ANY.png");
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
