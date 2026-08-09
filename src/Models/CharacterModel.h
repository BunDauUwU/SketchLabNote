// src/Models/CharacterModel.h
#pragma once

#include <QObject>
#include <QString>
#include "../Core/Enums.h"
#include "../Core/GameSnapshot.h"

class CharacterModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString characterId READ characterId WRITE setCharacterId NOTIFY characterIdChanged)
    Q_PROPERTY(int hp READ hp WRITE setHp NOTIFY hpChanged)
    Q_PROPERTY(int maxHp READ maxHp WRITE setMaxHp NOTIFY maxHpChanged)
    Q_PROPERTY(int energy READ energy WRITE setEnergy NOTIFY energyChanged)
    Q_PROPERTY(int maxEnergy READ maxEnergy WRITE setMaxEnergy NOTIFY maxEnergyChanged)
    Q_PROPERTY(QString element READ elementText NOTIFY elementChanged)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool defeated READ isDefeated WRITE setDefeated NOTIFY defeatedChanged)
    Q_PROPERTY(QString avatarPath READ avatarPath NOTIFY avatarPathChanged)

public:
    explicit CharacterModel(QObject* parent = nullptr);

    QString characterId() const { return m_characterId; }
    void setCharacterId(const QString& id);

    int hp() const { return m_hp; }
    void setHp(int hp);

    int maxHp() const { return m_maxHp; }
    void setMaxHp(int maxHp);

    int energy() const { return m_energy; }
    void setEnergy(int energy);

    int maxEnergy() const { return m_maxEnergy; }
    void setMaxEnergy(int maxEnergy);

    ElementType element() const { return m_element; }
    QString elementText() const;
    void setElement(ElementType element);

    bool isActive() const { return m_active; }
    void setActive(bool active);

    bool isDefeated() const { return m_defeated; }
    void setDefeated(bool defeated);

    QString avatarPath() const;

    void updateFromSnapshot(const CharacterState& state);

signals:
    void characterIdChanged();
    void hpChanged();
    void maxHpChanged();
    void energyChanged();
    void maxEnergyChanged();
    void elementChanged();
    void activeChanged();
    void defeatedChanged();
    void avatarPathChanged();

private:
    QString m_characterId;
    int m_hp = 10;
    int m_maxHp = 10;
    int m_energy = 0;
    int m_maxEnergy = 2;
    ElementType m_element = ElementType::None;
    bool m_active = false;
    bool m_defeated = false;
};
