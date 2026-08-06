#include <bits/stdc++.h>
#include <QObject>

#include "Enums.h"

struct CharacterState {
    QString characterId;
    int hp = 10;
    int maxHp = 10;
    int energy = 0;
    int maxEnergy = 2;
    ElementType element = ElementType::None;
    bool active = false;
    bool defeated = false;
};

struct PlayerPublicState {
    QString playerId;
    QString nickname;
    QVector<CharacterState> characters;
    int handCardCount = 0;
    int deckCardCount = 0;
    int activeCharacterIndex = -1;
};

struct PlayerPrivateState {
    QVector<QString> handCardIds;
    QVector<ElementType> dice;
};

struct GameSnapshot {
    QString matchId;
    GameStage stage = GameStage::None;
    int round = 0;
    int currentPlayerIndex = -1;
    QVector<PlayerPublicState> players;
    PlayerPrivateState self;
};