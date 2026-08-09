// src/Models/PlayerModel.h
#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include "../Core/GameSnapshot.h"
#include "CharacterModel.h"

class PlayerModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString playerId READ playerId WRITE setPlayerId NOTIFY playerIdChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(int elementPoints READ elementPoints WRITE setElementPoints NOTIFY elementPointsChanged)
    Q_PROPERTY(int maxElementPoints READ maxElementPoints WRITE setMaxElementPoints NOTIFY maxElementPointsChanged)
    Q_PROPERTY(int permanentEpBonus READ permanentEpBonus WRITE setPermanentEpBonus NOTIFY permanentEpBonusChanged)
    Q_PROPERTY(int handCardCount READ handCardCount WRITE setHandCardCount NOTIFY handCardCountChanged)
    Q_PROPERTY(int deckCardCount READ deckCardCount WRITE setDeckCardCount NOTIFY deckCardCountChanged)
    Q_PROPERTY(int activeCharacterIndex READ activeCharacterIndex WRITE setActiveCharacterIndex NOTIFY activeCharacterIndexChanged)

public:
    explicit PlayerModel(QObject* parent = nullptr);

    QString playerId() const { return m_playerId; }
    void setPlayerId(const QString& id);

    QString nickname() const { return m_nickname; }
    void setNickname(const QString& nick);

    int elementPoints() const { return m_elementPoints; }
    void setElementPoints(int ep);

    int maxElementPoints() const { return m_maxElementPoints; }
    void setMaxElementPoints(int maxEp);

    int permanentEpBonus() const { return m_permanentEpBonus; }
    void setPermanentEpBonus(int bonus);

    int handCardCount() const { return m_handCardCount; }
    void setHandCardCount(int count);

    int deckCardCount() const { return m_deckCardCount; }
    void setDeckCardCount(int count);

    int activeCharacterIndex() const { return m_activeCharacterIndex; }
    void setActiveCharacterIndex(int index);

    Q_INVOKABLE CharacterModel* getCharacter(int index) const;
    QVector<CharacterModel*> characters() const { return m_characters; }

    void updateFromSnapshot(const PlayerPublicState& state);

signals:
    void playerIdChanged();
    void nicknameChanged();
    void elementPointsChanged();
    void maxElementPointsChanged();
    void permanentEpBonusChanged();
    void handCardCountChanged();
    void deckCardCountChanged();
    void activeCharacterIndexChanged();

private:
    QString m_playerId;
    QString m_nickname;
    int m_elementPoints = 10;
    int m_maxElementPoints = 10;
    int m_permanentEpBonus = 0;
    int m_handCardCount = 0;
    int m_deckCardCount = 0;
    int m_activeCharacterIndex = -1;
    QVector<CharacterModel*> m_characters;
};
