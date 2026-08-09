// src/Models/CharacterModel.cpp
#include "CharacterModel.h"
#include "../Core/EnumUtils.h"
#include "../Data/AssetResolver.h"

CharacterModel::CharacterModel(QObject* parent) : QObject(parent)
{
}

void CharacterModel::setCharacterId(const QString& id)
{
    if (m_characterId == id) return;
    m_characterId = id;
    emit characterIdChanged();
    emit avatarPathChanged();
}

void CharacterModel::setHp(int hp)
{
    if (m_hp == hp) return;
    m_hp = hp;
    emit hpChanged();
}

void CharacterModel::setMaxHp(int maxHp)
{
    if (m_maxHp == maxHp) return;
    m_maxHp = maxHp;
    emit maxHpChanged();
}

void CharacterModel::setEnergy(int energy)
{
    if (m_energy == energy) return;
    m_energy = energy;
    emit energyChanged();
}

void CharacterModel::setMaxEnergy(int maxEnergy)
{
    if (m_maxEnergy == maxEnergy) return;
    m_maxEnergy = maxEnergy;
    emit maxEnergyChanged();
}

QString CharacterModel::elementText() const
{
    return EnumUtils::toString(m_element);
}

void CharacterModel::setElement(ElementType element)
{
    if (m_element == element) return;
    m_element = element;
    emit elementChanged();
}

void CharacterModel::setActive(bool active)
{
    if (m_active == active) return;
    m_active = active;
    emit activeChanged();
}

void CharacterModel::setDefeated(bool defeated)
{
    if (m_defeated == defeated) return;
    m_defeated = defeated;
    emit defeatedChanged();
}

QString CharacterModel::avatarPath() const
{
    return AssetResolver::resolveCharacterImage(m_characterId);
}

void CharacterModel::updateFromSnapshot(const CharacterState& state)
{
    setCharacterId(state.characterId);
    setHp(state.hp);
    setMaxHp(state.maxHp);
    setEnergy(state.energy);
    setMaxEnergy(state.maxEnergy);
    setElement(state.element);
    setActive(state.active);
    setDefeated(state.defeated);
}
