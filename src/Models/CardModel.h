// src/Models/CardModel.h
#pragma once

#include <QObject>
#include <QString>
#include "../Core/Enums.h"

class CardModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString cardId READ cardId WRITE setCardId NOTIFY cardIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ typeText NOTIFY typeChanged)
    Q_PROPERTY(int epCost READ epCost WRITE setEpCost NOTIFY epCostChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString imagePath READ imagePath NOTIFY imagePathChanged)

public:
    explicit CardModel(QObject* parent = nullptr);

    QString cardId() const { return m_cardId; }
    void setCardId(const QString& id);

    QString name() const { return m_name; }
    void setName(const QString& name);

    CardType type() const { return m_type; }
    QString typeText() const;
    void setType(CardType type);

    int epCost() const { return m_epCost; }
    void setEpCost(int cost);

    QString description() const { return m_description; }
    void setDescription(const QString& desc);

    QString imagePath() const;

signals:
    void cardIdChanged();
    void nameChanged();
    void typeChanged();
    void epCostChanged();
    void descriptionChanged();
    void imagePathChanged();

private:
    QString m_cardId;
    QString m_name;
    CardType m_type = CardType::Event;
    int m_epCost = 0;
    QString m_description;
};
