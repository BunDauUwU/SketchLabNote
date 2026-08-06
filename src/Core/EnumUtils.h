// src/Core/EnumUtils.h
#pragma once

#include <QString>

#include "Enums.h"

namespace EnumUtils {

QString toString(ElementType type);
ElementType elementTypeFromString(const QString& value);

QString toString(WeatherType type);
WeatherType weatherTypeFromString(const QString& value);

QString toString(GameStage stage);
GameStage gameStageFromString(const QString& value);

QString toString(CardType type);
CardType cardTypeFromString(const QString& value);

QString toString(NetworkMessageType type);
NetworkMessageType networkMessageTypeFromString(const QString& value);

QString toString(GameCommandType type);
GameCommandType gameCommandTypeFromString(const QString& value);

QString toString(GameEventType type);
GameEventType gameEventTypeFromString(const QString& value);

QString toString(ZoneType type);
ZoneType zoneTypeFromString(const QString& value);

}