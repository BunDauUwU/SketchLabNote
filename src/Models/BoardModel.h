// src/Models/BoardModel.h
#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include "../Core/Enums.h"
#include "../Core/GameSnapshot.h"
#include "PlayerModel.h"

class BoardModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString matchId READ matchId NOTIFY matchIdChanged)
    Q_PROPERTY(int round READ round NOTIFY roundChanged)
    Q_PROPERTY(QString stage READ stageText NOTIFY stageChanged)

    Q_PROPERTY(QString currentWeather READ currentWeatherText NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherName READ weatherName NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherDescription READ weatherDescription NOTIFY weatherChanged)
    Q_PROPERTY(QString weatherIcon READ weatherIcon NOTIFY weatherChanged)
    Q_PROPERTY(int weatherRemainingRounds READ weatherRemainingRounds NOTIFY weatherChanged)
    Q_PROPERTY(QStringList weatherSequence READ weatherSequence NOTIFY weatherChanged)

    Q_PROPERTY(PlayerModel* selfPlayer READ selfPlayer NOTIFY selfPlayerChanged)
    Q_PROPERTY(PlayerModel* opponentPlayer READ opponentPlayer NOTIFY opponentPlayerChanged)
    Q_PROPERTY(bool isMyTurn READ isMyTurn NOTIFY turnChanged)

public:
    explicit BoardModel(QObject* parent = nullptr);

    QString matchId() const { return m_matchId; }
    int round() const { return m_round; }
    GameStage stage() const { return m_stage; }
    QString stageText() const;

    WeatherType currentWeather() const { return m_weather.type; }
    QString currentWeatherText() const;
    QString weatherName() const;
    QString weatherDescription() const;
    QString weatherIcon() const;
    int weatherRemainingRounds() const { return m_weather.remainingRounds; }
    QStringList weatherSequence() const;

    PlayerModel* selfPlayer() const { return m_selfPlayer; }
    PlayerModel* opponentPlayer() const { return m_opponentPlayer; }
    bool isMyTurn() const { return m_isMyTurn; }

    void updateFromSnapshot(const GameSnapshot& snapshot, int localPlayerIndex);

signals:
    void matchIdChanged();
    void roundChanged();
    void stageChanged();
    void weatherChanged();
    void selfPlayerChanged();
    void opponentPlayerChanged();
    void turnChanged();

private:
    QString m_matchId;
    int m_round = 1;
    GameStage m_stage = GameStage::None;
    WeatherState m_weather;
    QVector<WeatherType> m_weatherPlanSequence;
    PlayerModel* m_selfPlayer = nullptr;
    PlayerModel* m_opponentPlayer = nullptr;
    bool m_isMyTurn = false;
};
