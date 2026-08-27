#pragma once

#include <QObject>
#include <QStringList>
#include <QJsonObject>
#include <QVariantMap>

class CardDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList cardList READ cardList NOTIFY cardListChanged)

public:
    explicit CardDatabase(QObject *parent = nullptr);

    QStringList cardList() const;

    Q_INVOKABLE QString name(const int index);
    Q_INVOKABLE QString skills(const int index);
    Q_INVOKABLE int cost(const QString& cardId) const;
    Q_INVOKABLE QVariantMap details(const QString& cardId) const;
    Q_INVOKABLE void handlecardClick(int index);

signals:
    void cardSelected(const QString &cardId);
    void cardListChanged();

private:
    QStringList m_cardList;
    QStringList m_cardName;
    QJsonObject m_cardInfo;
};
