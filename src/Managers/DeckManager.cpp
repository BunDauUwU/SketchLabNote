#include "DeckManager.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QStandardPaths>
#include <QDateTime>

DeckManager::DeckManager(QObject *parent) : QObject(parent)
{

}

void DeckManager::initDatabase()
{
    const QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataDir);
    if (!dir.exists()) {
        dir.mkpath(appDataDir);
    }

    const QString dbPath = dir.filePath(QStringLiteral("users.sqlite"));
    QSqlDatabase db;

    if (QSqlDatabase::contains(QStringLiteral("AuthConnection"))) {
        db = QSqlDatabase::database(QStringLiteral("AuthConnection"));
    } else {
        db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), QStringLiteral("AuthConnection"));
        db.setDatabaseName(dbPath);
    }

    if (!db.open()) {
        qWarning() << "Failed to open Auth SQLite database:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
}

QStringList DeckManager::cards() const
{
    return m_cards;
}

QStringList DeckManager::characters() const
{
    return m_characters;
}

bool DeckManager::addCharacter(const QString &cardId, const QString& username, int &deckIndex)
{
    if (cardId.isEmpty())
        return false;

    if (m_characters.size() >= 3) {
        emit errorOccurred(QStringLiteral("Maximum 3 characters allowed"));
        return false;
    }

    if (m_characters.count(cardId)){
        emit errorOccurred(QStringLiteral("These characters have no twwin"));
        return false;
    }

    m_characters.append(cardId);
    emit charactersChanged();
    emit deckChanged();
    saveDeck(username, deckIndex);
    return true;
}

bool DeckManager::removeCharacter(const QString &cardId, const QString& username, int &deckIndex)
{
    if (!m_characters.contains(cardId))
        return false;

    m_characters.removeOne(cardId);
    emit charactersChanged();
    emit deckChanged();
    saveDeck(username, deckIndex);
    return true;
}

bool DeckManager::addCard(const QString &cardId, const QString& username, int &deckIndex)
{
    if (cardId.isEmpty())
        return false;

    if (m_cards.size() >= 30) {
        emit errorOccurred(QStringLiteral("Maximum 30 cards allowed"));
        return false;
    }

    if(m_cards.count(cardId) > 3) {
        emit errorOccurred(QStringLiteral("Maximum 3 copies of a card allowed"));
        return false;
    }

    m_cards.append(cardId);

    emit cardsChanged();
    emit deckChanged();

    saveDeck(username, deckIndex);

    return true;
}

bool DeckManager::removeCard(const QString &cardId, const QString& username, int &deckIndex)
{
    if (!m_cards.contains(cardId))
        return false;

    m_cards.removeOne(cardId);
    emit cardsChanged();
    emit deckChanged();
    saveDeck(username, deckIndex);
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

void DeckManager::saveDeck(const QString& username, int &deckIndex)
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

    QSqlDatabase db = QSqlDatabase::database(QStringLiteral("SaveDeck"));

    if (!db.isOpen() && !db.open()) {
        qDebug() << "Database connection failed"  << '\n';
        return ;
    }

    const QString cleanUser = username.trimmed();
    QSqlQuery query(db);
    query.prepare(QStringLiteral("SELECT decks FROM users WHERE username = :user"));
    query.bindValue(QStringLiteral(":user"), cleanUser);
    if(!query.exec() || !query.next()) {
        qDebug() << "Failed to write deck"  << '\n';
        emit errorOccurred(QStringLiteral("Failed to open deck file for writing"));
        return ;
    }


    // QFile file(deckFilePath());
    // if (file.open(QIODevice::WriteOnly)) {

    //     file.write(QJsonDocument(root).toJson());
    // } else {
    //     emit errorOccurred(QStringLiteral("Failed to open deck file for writing"));
    // }
}

void DeckManager::loadDeck(const QString& username, int &deckIndex)
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


