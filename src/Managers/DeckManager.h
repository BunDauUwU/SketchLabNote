#pragma once

#include <QObject>
#include <QStringList>
#include <QVariantList>

class DeckManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList cards READ cards NOTIFY cardsChanged)
    Q_PROPERTY(QStringList characters READ characters NOTIFY charactersChanged)
    Q_PROPERTY(QVariantList validDecks READ validDecks NOTIFY validDecksChanged)

public:
    explicit DeckManager(QObject *parent = nullptr);

    QStringList cards() const;
    QStringList characters() const;
    QVariantList validDecks() const { return m_validDecks; }
    int deckIndex() const {return deckIdx;};


    Q_INVOKABLE void changeDeckIndex(int val);
    Q_INVOKABLE bool addCharacter(const QString &cardId, const QString& username);
    Q_INVOKABLE bool removeCharacter(const QString &cardId, const QString& username);

    Q_INVOKABLE bool addCard(const QString &cardId, const QString& username);
    Q_INVOKABLE bool removeCard(const QString &cardId, const QString& username);

    Q_INVOKABLE void saveDeck(const QString& username);
    Q_INVOKABLE void loadDeck(const QString& username);
    Q_INVOKABLE void refreshValidDecks(const QString& username);

signals:
    void cardsChanged();
    void charactersChanged();
    void deckIndexChanged();
    void deckChanged();
    void validDecksChanged();
    void errorOccurred(const QString &message);

private:
    void initDatabase();

    QStringList m_cards;
    QStringList m_characters;
    int deckIdx = 1;
    QVariantList m_validDecks;

    QString deckFilePath() const;
};
