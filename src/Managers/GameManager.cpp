// src/Managers/GameManager.cpp
#include "GameManager.h"

#include "../Core/EnumUtils.h"
#include "../Network/Protocol.h"

#include <QJsonArray>

GameManager::GameManager(QObject* parent)
    : QObject(parent)
{
}

void GameManager::setNetworkClient(NetworkClient* networkClient)
{
    m_networkClient = networkClient;
}

QString GameManager::matchId() const
{
    return m_matchId;
}

int GameManager::playerIndex() const
{
    return m_playerIndex;
}

QString GameManager::opponentName() const
{
    return m_opponentName;
}

QString GameManager::stageText() const
{
    return EnumUtils::toString(m_stage);
}

void GameManager::setMatchInfo(
    const QString& matchId,
    int playerIndex,
    const QString& opponentName
    )
{
    if (m_matchId != matchId) {
        m_matchId = matchId;
        emit matchIdChanged();
    }

    if (m_playerIndex != playerIndex) {
        m_playerIndex = playerIndex;
        emit playerIndexChanged();
    }

    if (m_opponentName != opponentName) {
        m_opponentName = opponentName;
        emit opponentNameChanged();
    }
}

void GameManager::chooseActiveCharacter(int characterIndex)
{
    if (m_matchId.isEmpty()) {
        emit gameError(QStringLiteral("No active match"));
        return;
    }

    sendCommand(
        Protocol::makeChooseActiveCharacterCommand(m_matchId, characterIndex)
        );
}

void GameManager::endRound()
{
    if (m_matchId.isEmpty()) {
        emit gameError(QStringLiteral("No active match"));
        return;
    }

    sendCommand(
        Protocol::makeEndRoundCommand(m_matchId)
        );
}

void GameManager::useSkill(
    int skillIndex,
    const QVariantList& diceIndexes,
    const QVariantMap& target
    )
{
    if (m_matchId.isEmpty()) {
        emit gameError(QStringLiteral("No active match"));
        return;
    }

    sendCommand(
        Protocol::makeUseSkillCommand(
            m_matchId,
            skillIndex,
            diceIndexes,
            target
            )
        );
}

void GameManager::playCard(
    int handIndex,
    const QVariantList& diceIndexes,
    const QVariantMap& target
    )
{
    if (m_matchId.isEmpty()) {
        emit gameError(QStringLiteral("No active match"));
        return;
    }

    sendCommand(
        Protocol::makePlayCardCommand(
            m_matchId,
            handIndex,
            diceIndexes,
            target
            )
        );
}

void GameManager::handleServerMessage(const QJsonObject& message)
{
    const QString type = Protocol::readMessageType(message);
    const QJsonObject payload = Protocol::readPayload(message);

    if (type == "GameSnapshot") {
        const QString matchId = payload.value("matchId").toString();

        if (!matchId.isEmpty() && matchId != m_matchId) {
            return;
        }

        const QString stage = payload.value("stage").toString();
        setStage(EnumUtils::gameStageFromString(stage));

        emit gameSnapshotReceived(payload);
        return;
    }

    if (type == "GameEvent") {
        const QString matchId = payload.value("matchId").toString();

        if (!matchId.isEmpty() && matchId != m_matchId) {
            return;
        }

        const QJsonArray events = payload.value("events").toArray();

        for (const QJsonValue& value : events) {
            const QJsonObject event = value.toObject();
            const QString eventType = event.value("eventType").toString();

            if (eventType == "StageChanged") {
                const QString nextStage = event.value("stage").toString();
                setStage(EnumUtils::gameStageFromString(nextStage));
            }

            if (eventType == "GameEnded") {
                emit gameEnded(event.value("reason").toString());
            }
        }

        emit gameEventsReceived(events);
        return;
    }

    if (type == "Error") {
        emit gameError(payload.value("message").toString());
    }
}

void GameManager::setStage(GameStage stage)
{
    if (m_stage == stage) {
        return;
    }

    m_stage = stage;
    emit stageChanged();
}

void GameManager::sendCommand(const QJsonObject& command)
{
    if (!m_networkClient) {
        emit gameError(QStringLiteral("Network client is not ready"));
        return;
    }

    if (!m_networkClient->isConnected()) {
        emit gameError(QStringLiteral("Not connected to server"));
        return;
    }

    m_networkClient->sendMessage(command);
}