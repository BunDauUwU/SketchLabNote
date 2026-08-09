// src/Models/BoardModel.cpp
#include "BoardModel.h"
#include "../Core/EnumUtils.h"
#include "../Data/AssetResolver.h"

BoardModel::BoardModel(QObject* parent)
    : QObject(parent)
    , m_selfPlayer(new PlayerModel(this))
    , m_opponentPlayer(new PlayerModel(this))
{
}

QString BoardModel::stageText() const
{
    return EnumUtils::toString(m_stage);
}

QString BoardModel::currentWeatherText() const
{
    return EnumUtils::toString(m_weather.type);
}

QString BoardModel::weatherName() const
{
    return AssetResolver::resolveWeatherName(m_weather.type);
}

QString BoardModel::weatherDescription() const
{
    return AssetResolver::resolveWeatherDescription(m_weather.type);
}

QString BoardModel::weatherIcon() const
{
    return AssetResolver::resolveWeatherIcon(m_weather.type);
}

QStringList BoardModel::weatherSequence() const
{
    QStringList seq;
    for (WeatherType w : m_weatherPlanSequence) {
        seq.append(EnumUtils::toString(w));
    }
    return seq;
}

void BoardModel::updateFromSnapshot(const GameSnapshot& snapshot, int localPlayerIndex)
{
    if (m_matchId != snapshot.matchId) {
        m_matchId = snapshot.matchId;
        emit matchIdChanged();
    }

    if (m_round != snapshot.round) {
        m_round = snapshot.round;
        emit roundChanged();
    }

    if (m_stage != snapshot.stage) {
        m_stage = snapshot.stage;
        emit stageChanged();
    }

    if (m_weather.type != snapshot.weather.activeWeather.type ||
        m_weather.remainingRounds != snapshot.weather.activeWeather.remainingRounds ||
        m_weatherPlanSequence != snapshot.weather.sequence) {
        m_weather = snapshot.weather.activeWeather;
        m_weatherPlanSequence = snapshot.weather.sequence;
        emit weatherChanged();
    }

    const bool myTurn = (snapshot.currentPlayerIndex == localPlayerIndex);
    if (m_isMyTurn != myTurn) {
        m_isMyTurn = myTurn;
        emit turnChanged();
    }

    for (int i = 0; i < snapshot.players.size(); ++i) {
        if (i == localPlayerIndex) {
            m_selfPlayer->updateFromSnapshot(snapshot.players.at(i));
        } else {
            m_opponentPlayer->updateFromSnapshot(snapshot.players.at(i));
        }
    }
}
