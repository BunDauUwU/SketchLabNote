// src/Network/Protocol.cpp
#include "Protocol.h"

#include <QJsonDocument>

#include "../Core/EnumUtils.h"

namespace {

QJsonArray stringListToJsonArray(const QStringList& values)
{
    QJsonArray array;

    for (const QString& value : values) {
        array.append(value);
    }

    return array;
}

QJsonArray variantListToJsonArray(const QVariantList& values)
{
    QJsonArray array;

    for (const QVariant& value : values) {
        array.append(QJsonValue::fromVariant(value));
    }

    return array;
}

QJsonObject variantMapToJsonObject(const QVariantMap& values)
{
    QJsonObject object;

    for (auto it = values.constBegin(); it != values.constEnd(); ++it) {
        object.insert(it.key(), QJsonValue::fromVariant(it.value()));
    }

    return object;
}

}

namespace Protocol {

QJsonObject makeEnvelope(NetworkMessageType type, const QJsonObject& payload)
{
    QJsonObject message;
    message["type"] = EnumUtils::toString(type);
    message["payload"] = payload;

    return message;
}

QJsonObject makeErrorPayload(const QString& code, const QString& message)
{
    QJsonObject payload;
    payload["code"] = code;
    payload["message"] = message;

    return payload;
}

QJsonObject makeAuthRequest(const QString& nickname)
{
    QJsonObject payload;
    payload["mode"] = "guest";
    payload["nickname"] = nickname;

    return makeEnvelope(NetworkMessageType::AuthRequest, payload);
}

QJsonObject makeStartMatchmaking(const QString& mode, const QString& deckId)
{
    QJsonObject payload;
    payload["mode"] = mode;
    payload["deckId"] = deckId;

    return makeEnvelope(NetworkMessageType::MatchmakingStart, payload);
}

QJsonObject makeCancelMatchmaking()
{
    return makeEnvelope(NetworkMessageType::MatchmakingCancel, QJsonObject{});
}

QJsonObject makeSubmitDeck(
    const QString& deckId,
    const QStringList& characterIds,
    const QStringList& cardIds
    )
{
    QJsonObject payload;
    payload["deckId"] = deckId;
    payload["characters"] = stringListToJsonArray(characterIds);
    payload["cards"] = stringListToJsonArray(cardIds);

    return makeEnvelope(NetworkMessageType::SubmitDeck, payload);
}

QJsonObject makeGameCommand(
    const QString& matchId,
    GameCommandType commandType,
    const QJsonObject& commandPayload
    )
{
    QJsonObject payload;
    payload["matchId"] = matchId;
    payload["commandType"] = EnumUtils::toString(commandType);
    payload["command"] = commandPayload;

    return makeEnvelope(NetworkMessageType::GameCommand, payload);
}

QJsonObject makeChooseActiveCharacterCommand(
    const QString& matchId,
    int characterIndex
    )
{
    QJsonObject command;
    command["characterIndex"] = characterIndex;

    return makeGameCommand(
        matchId,
        GameCommandType::ChooseActiveCharacter,
        command
        );
}

QJsonObject makeEndRoundCommand(const QString& matchId)
{
    return makeGameCommand(
        matchId,
        GameCommandType::EndRound,
        QJsonObject{}
        );
}

QJsonObject makeUseSkillCommand(
    const QString& matchId,
    int skillIndex,
    const QVariantList& diceIndexes,
    const QVariantMap& target
    )
{
    QJsonObject command;
    command["skillIndex"] = skillIndex;
    command["diceIndexes"] = variantListToJsonArray(diceIndexes);
    command["target"] = variantMapToJsonObject(target);

    return makeGameCommand(
        matchId,
        GameCommandType::UseSkill,
        command
        );
}

QJsonObject makePlayCardCommand(
    const QString& matchId,
    int handIndex,
    const QVariantList& diceIndexes,
    const QVariantMap& target
    )
{
    QJsonObject command;
    command["handIndex"] = handIndex;
    command["diceIndexes"] = variantListToJsonArray(diceIndexes);
    command["target"] = variantMapToJsonObject(target);

    return makeGameCommand(
        matchId,
        GameCommandType::PlayCard,
        command
        );
}

QString readMessageType(const QJsonObject& message)
{
    return message.value("type").toString("Unknown");
}

QJsonObject readPayload(const QJsonObject& message)
{
    return message.value("payload").toObject();
}

}