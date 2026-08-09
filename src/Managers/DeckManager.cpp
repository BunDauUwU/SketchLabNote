#include "DeckManager.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDebug>

DeckManager::DeckManager(QObject *parent) : QObject(parent)
{
    loadDeck();
}

QStringList DeckManager::cards() const
{
    return m_cards;
}

QStringList DeckManager::characters() const
{
    return m_characters;
}

bool DeckManager::addCharacter(const QString &cardId)
{
    if (cardId.isEmpty())
        return false;

    if (m_characters.size() >= 3) {
        emit errorOccurred(QStringLiteral("Maximum 3 characters allowed in a deck"));
        return false;
    }

    m_characters.append(cardId);
    emit charactersChanged();
    emit deckChanged();
    saveDeck();
    return true;
}

bool DeckManager::removeCharacter(const QString &cardId)
{
    if (!m_characters.contains(cardId))
        return false;

    m_characters.removeOne(cardId);
    emit charactersChanged();
    emit deckChanged();
    saveDeck();
    return true;
}

bool DeckManager::addCard(const QString &cardId)
{
    if (cardId.isEmpty())
        return false;

    if (m_cards.size() >= 30) {
        emit errorOccurred(QStringLiteral("Maximum 30 cards allowed in a deck"));
        return false;
    }

    m_cards.append(cardId);

    emit cardsChanged();
    emit deckChanged();

    saveDeck();

    return true;
}

bool DeckManager::removeCard(const QString &cardId)
{
    if (!m_cards.contains(cardId))
        return false;

    m_cards.removeOne(cardId);
    emit cardsChanged();
    emit deckChanged();
    saveDeck();
    return true;
}

QString DeckManager::deckFilePath() const
{
    const QString appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appData);
    if (!dir.exists()) {
        dir.mkpath(appData);
    }
    return dir.filePath(QStringLiteral("deck.json"));
}

void DeckManager::saveDeck()
{
    QJsonObject root;
    QJsonArray charsArray;
    for (const QString &c : m_characters) {
        charsArray.append(c);
    }
    QJsonArray cardsArray;
    for (const QString &c : m_cards) {
        cardsArray.append(c);
    }
    root["characters"] = charsArray;
    root["cards"] = cardsArray;

    QFile file(deckFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
    } else {
        emit errorOccurred(QStringLiteral("Failed to open deck file for writing"));
    }
}

void DeckManager::loadDeck()
{
    QFile file(deckFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
        return;

    QJsonObject root = doc.object();
    m_characters.clear();
    const QJsonArray charsArray = root.value("characters").toArray();
    for (const QJsonValue &v : charsArray) {
        m_characters.append(v.toString());
    }

    m_cards.clear();
    const QJsonArray cardsArray = root.value("cards").toArray();
    for (const QJsonValue &v : cardsArray) {
        m_cards.append(v.toString());
    }

    emit charactersChanged();
    emit cardsChanged();
    emit deckChanged();
}


