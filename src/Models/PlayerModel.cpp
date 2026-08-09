// src/Models/PlayerModel.cpp
#include "PlayerModel.h"

PlayerModel::PlayerModel(QObject* parent) : QObject(parent)
{
}

void PlayerModel::setPlayerId(const QString& id)
{
    if (m_playerId == id) return;
    m_playerId = id;
    emit playerIdChanged();
}

void PlayerModel::setNickname(const QString& nick)
{
    if (m_nickname == nick) return;
    m_nickname = nick;
    emit nicknameChanged();
}

void PlayerModel::setElementPoints(int ep)
{
    if (m_elementPoints == ep) return;
    m_elementPoints = ep;
    emit elementPointsChanged();
}

void PlayerModel::setMaxElementPoints(int maxEp)
{
    if (m_maxElementPoints == maxEp) return;
    m_maxElementPoints = maxEp;
    emit maxElementPointsChanged();
}

void PlayerModel::setPermanentEpBonus(int bonus)
{
    if (m_permanentEpBonus == bonus) return;
    m_permanentEpBonus = bonus;
    emit permanentEpBonusChanged();
}

void PlayerModel::setHandCardCount(int count)
{
    if (m_handCardCount == count) return;
    m_handCardCount = count;
    emit handCardCountChanged();
}

void PlayerModel::setDeckCardCount(int count)
{
    if (m_deckCardCount == count) return;
    m_deckCardCount = count;
    emit deckCardCountChanged();
}

void PlayerModel::setActiveCharacterIndex(int index)
{
    if (m_activeCharacterIndex == index) return;
    m_activeCharacterIndex = index;
    emit activeCharacterIndexChanged();
}

CharacterModel* PlayerModel::getCharacter(int index) const
{
    if (index < 0 || index >= m_characters.size()) return nullptr;
    return m_characters.at(index);
}

void PlayerModel::updateFromSnapshot(const PlayerPublicState& state)
{
    setPlayerId(state.playerId);
    setNickname(state.nickname);
    setElementPoints(state.elementPoints.current);
    setMaxElementPoints(state.elementPoints.maximum);
    setPermanentEpBonus(state.elementPoints.permanentBonus);
    setHandCardCount(state.handCardCount);
    setDeckCardCount(state.deckCardCount);
    setActiveCharacterIndex(state.activeCharacterIndex);

    while (m_characters.size() < state.characters.size()) {
        m_characters.append(new CharacterModel(this));
    }
    while (m_characters.size() > state.characters.size()) {
        auto* charModel = m_characters.takeLast();
        charModel->deleteLater();
    }

    for (int i = 0; i < state.characters.size(); ++i) {
        m_characters[i]->updateFromSnapshot(state.characters.at(i));
    }
}
