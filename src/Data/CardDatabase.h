#pragma once

#include <QObject>
#include <QStringList>

class CardDatabase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList cardList READ cardList NOTIFY cardListChanged)

public:
    explicit CardDatabase(QObject *parent = nullptr);

    QStringList cardList() const;

    Q_INVOKABLE void handlecardClick(int index);

signals:
    void cardSelected(const QString &cardId);
    void cardListChanged();

private:
    QStringList m_cardList;
};