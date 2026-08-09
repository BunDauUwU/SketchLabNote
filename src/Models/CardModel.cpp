// src/Models/CardModel.cpp
#include "CardModel.h"
#include "../Core/EnumUtils.h"
#include "../Data/AssetResolver.h"

CardModel::CardModel(QObject* parent) : QObject(parent)
{
}

void CardModel::setCardId(const QString& id)
{
    if (m_cardId == id) return;
    m_cardId = id;
    emit cardIdChanged();
    emit imagePathChanged();
}

void CardModel::setName(const QString& name)
{
    if (m_name == name) return;
    m_name = name;
    emit nameChanged();
}

QString CardModel::typeText() const
{
    return EnumUtils::toString(m_type);
}

void CardModel::setType(CardType type)
{
    if (m_type == type) return;
    m_type = type;
    emit typeChanged();
}

void CardModel::setEpCost(int cost)
{
    if (m_epCost == cost) return;
    m_epCost = cost;
    emit epCostChanged();
}

void CardModel::setDescription(const QString& desc)
{
    if (m_description == desc) return;
    m_description = desc;
    emit descriptionChanged();
}

QString CardModel::imagePath() const
{
    return AssetResolver::resolveCardImage(m_cardId);
}
