// src/Data/AssetResolver.h
#pragma once

#include <QObject>
#include <QString>
#include "../Core/Enums.h"

class AssetResolver : public QObject {
    Q_OBJECT

public:
    explicit AssetResolver(QObject* parent = nullptr);

    Q_INVOKABLE static QString resolveCardImage(const QString& cardId);
    Q_INVOKABLE static QString resolveCharacterImage(const QString& charId);
    Q_INVOKABLE static QString resolveElementIcon(ElementType element);
    Q_INVOKABLE static QString resolveWeatherIcon(WeatherType weather);
    Q_INVOKABLE static QString resolveWeatherName(WeatherType weather);
    Q_INVOKABLE static QString resolveWeatherDescription(WeatherType weather);
};
