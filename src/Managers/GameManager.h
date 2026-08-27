// src/Managers/GameManager.h
#pragma once

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QVariantMap>
#include <QStringList>

#include "../Core/Enums.h"
#include "../Network/NetworkClient.h"
#include "../Models/BoardModel.h"

class GameManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString matchId READ matchId NOTIFY matchIdChanged)
    Q_PROPERTY(int playerIndex READ playerIndex NOTIFY playerIndexChanged)
    Q_PROPERTY(QString opponentName READ opponentName NOTIFY opponentNameChanged)
    Q_PROPERTY(QString stage READ stageText NOTIFY stageChanged)
    Q_PROPERTY(BoardModel* board READ board CONSTANT)
    Q_PROPERTY(QStringList weatherSequence READ weatherSequence NOTIFY gamePrepared)
    Q_PROPERTY(int selectionSeconds READ selectionSeconds NOTIFY matchIdChanged)
    Q_PROPERTY(QVariantMap snapshot READ snapshot NOTIFY snapshotChanged)

public:
    explicit GameManager(QObject* parent = nullptr);

    void setNetworkClient(NetworkClient* networkClient);

    QString matchId() const;
    int playerIndex() const;
    QString opponentName() const;
    QString stageText() const;
    BoardModel* board() const { return m_board; }
    QStringList weatherSequence() const { return m_weatherSequence; }
    int selectionSeconds() const { return m_selectionSeconds; }
    QVariantMap snapshot() const { return m_snapshot; }

    Q_INVOKABLE void setMatchInfo(
        const QString& matchId,
        int playerIndex,
        const QString& opponentName
        );

    Q_INVOKABLE void chooseActiveCharacter(int characterIndex);
    Q_INVOKABLE void switchCharacter(int characterIndex);
    Q_INVOKABLE void endRound();

    Q_INVOKABLE void useSkill(
        int skillIndex,
        int elementPointCost,
        const QVariantMap& target
        );

    Q_INVOKABLE void playCard(
        int handIndex,
        int elementPointCost,
        const QVariantMap& target
        );
    Q_INVOKABLE void selectDeck(const QString& deckId, const QVariantList& characters, const QVariantList& cards);

signals:
    void matchIdChanged();
    void playerIndexChanged();
    void opponentNameChanged();
    void stageChanged();
    void snapshotChanged();

    void gamePrepared();
    void gameError(const QString& message);
    void gameSnapshotReceived(const QJsonObject& snapshot);
    void gameEventsReceived(const QJsonArray& events);
    void gameEnded(const QString& reason);

public slots:
    void handleServerMessage(const QJsonObject& message);

private:
    void setStage(GameStage stage);
    void sendCommand(const QJsonObject& command);

private:
    NetworkClient* m_networkClient = nullptr;

    QString m_matchId;
    int m_playerIndex = -1;
    QString m_opponentName;
    GameStage m_stage = GameStage::None;
    BoardModel* m_board = nullptr;
    QStringList m_weatherSequence;
    int m_selectionSeconds = 10;
    QVariantMap m_snapshot;
};
