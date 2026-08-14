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
    QJsonDocument doc(root);
    QString newDeckJsonString = doc.toJson(QJsonDocument::Compact);

    QSqlQuery query(db);
    query.prepare(
        "UPDATE users "
        "SET decks = json_set(decks, :deckId, json(:deck)) "
        "WHERE username = :user"
        );
    query.bindValue(QStringLiteral(":user"), cleanUser);

    if (deckIndex == 1) {
        query.bindValue(QStringLiteral(":deckId"), "$.deck1");
        query.bindValue(QStringLiteral(":decks"), newDeckJsonString);
    } else if (deckIndex == 2) {
        query.bindValue(QStringLiteral(":deckId"), "$.deck2");
        query.bindValue(QStringLiteral(":decks"), newDeckJsonString);
    } else {
        query.bindValue(QStringLiteral(":deckId"), "$.deck3");
        query.bindValue(QStringLiteral(":decks"), newDeckJsonString);
    }
}

void DeckManager::loadDeck(const QString& username, int &deckIndex)
{
    QSqlDatabase db = QSqlDatabase::database(QStringLiteral("LoadDeck"));

    if (!db.isOpen() && !db.open()) {
        qDebug() << "Database connection failed"  << '\n';
        return ;
    }

    const QString cleanUser = username.trimmed();
    QSqlQuery query(db);
    query.prepare(
        "SELECT decks -> :deckId FROM users WHERE username = :user"
    );
    query.bindValue(QStringLiteral(":user"), cleanUser);
    if (deckIndex == 1) {
        query.bindValue(QStringLiteral(":deckId"), "$.deck1");
    } else if (deckIndex == 2) {
        query.bindValue(QStringLiteral(":deckId"), "$.deck2");
    } else {
        query.bindValue(QStringLiteral(":deckId"), "$.deck3");
    }
    if (!query.exec() || !query.next()) {
        qDebug() << "Deck fetch failled"  << '\n';
        return ;
    }

    QString jsonString = query.value(0).toString();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());

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


