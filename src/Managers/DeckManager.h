#pragma once

#include <QObject>
#include <QStringList>

class DeckManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList cards READ cards NOTIFY cardsChanged)
    Q_PROPERTY(QStringList characters READ characters NOTIFY charactersChanged)

public:
    explicit DeckManager(QObject *parent = nullptr);

    QStringList cards() const;
    QStringList characters() const;

    Q_INVOKABLE bool addCharacter(const QString &cardId);
    Q_INVOKABLE bool removeCharacter(const QString &cardId);

    Q_INVOKABLE bool addCard(const QString &cardId);
    Q_INVOKABLE bool removeCard(const QString &cardId);

    Q_INVOKABLE void saveDeck();
    Q_INVOKABLE void loadDeck();

signals:
    void cardsChanged();
    void charactersChanged();
    void deckChanged();
    void errorOccurred(const QString &message);

private:
    QStringList m_cards;
    QStringList m_characters;

    QString deckFilePath() const;
};