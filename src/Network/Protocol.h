// src/Network/Protocol.h
#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QVariantMap>

#include "../Core/Enums.h"

namespace Protocol {

QJsonObject makeEnvelope(NetworkMessageType type, const QJsonObject& payload);
QJsonObject makeErrorPayload(const QString& code, const QString& message);

QJsonObject makeAuthRequest(const QString& nickname);
QJsonObject makeStartMatchmaking(const QString& mode, const QString& deckId);
QJsonObject makeCancelMatchmaking();

QJsonObject makeSubmitDeck(
    const QString& deckId,
    const QStringList& characterIds,
    const QStringList& cardIds
    );

QJsonObject makeGameCommand(
    const QString& matchId,
    GameCommandType commandType,
    const QJsonObject& commandPayload
    );

QJsonObject makeChooseActiveCharacterCommand(
    const QString& matchId,
    int characterIndex
    );

QJsonObject makeEndRoundCommand(const QString& matchId);

QJsonObject makeUseSkillCommand(
    const QString& matchId,
    int skillIndex,
    const QVariantList& diceIndexes,
    const QVariantMap& target
    );

QJsonObject makePlayCardCommand(
    const QString& matchId,
    int handIndex,
    const QVariantList& diceIndexes,
    const QVariantMap& target
    );

QString readMessageType(const QJsonObject& message);
QJsonObject readPayload(const QJsonObject& message);

}