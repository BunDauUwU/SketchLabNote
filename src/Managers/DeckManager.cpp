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
#include <QDateTime>
#include <QHash>
#include <QSet>

const QString DB_CONN_NAME = QStringLiteral("AuthConnection");

DeckManager::DeckManager(QObject *parent) : QObject(parent)
{
    initDatabase();
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

    if (QSqlDatabase::contains(DB_CONN_NAME)) {
        db = QSqlDatabase::database(DB_CONN_NAME);
    } else {
        db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), DB_CONN_NAME);
        db.setDatabaseName(dbPath);
    }

    if (!db.open()) {
        qWarning() << "Failed to open Auth SQLite database:" << db.lastError().text();
        return;
    }
    qDebug() << "Database initialized and opened successfully.";

}

void DeckManager::refreshValidDecks(const QString& username)
{
    m_validDecks.clear();
    QSqlDatabase db = QSqlDatabase::database(DB_CONN_NAME);
    if (!db.isOpen() && !db.open()) {
        emit errorOccurred(QStringLiteral("Unable to load battle decks"));
        emit validDecksChanged();
        return;
    }

    QSqlQuery query(db);
    query.prepare(QStringLiteral("SELECT decks FROM users WHERE username = :user"));
    query.bindValue(QStringLiteral(":user"), username.trimmed());
    if (!query.exec() || !query.next()) {
        emit validDecksChanged();
        return;
    }

    const QJsonObject root = QJsonDocument::fromJson(query.value(0).toString().toUtf8()).object();
    for (int index = 1; index <= 3; ++index) {
        const QJsonObject deck = root.value(QStringLiteral("deck%1").arg(index)).toObject();
        const QJsonArray characters = deck.value("characters").toArray();
        const QJsonArray cards = deck.value("cards").toArray();
        if (characters.size() != 3 || cards.size() != 30) continue;
        QSet<QString> uniqueCharacters;
        QHash<QString, int> cardCopies;
        bool valid = true;
        for (const QJsonValue& character : characters) {
            const QString id = character.toString().trimmed();
            if (id.isEmpty() || uniqueCharacters.contains(id)) valid = false;
            uniqueCharacters.insert(id);
        }
        for (const QJsonValue& card : cards) {
            const QString id = card.toString().trimmed();
            if (id.isEmpty() || ++cardCopies[id] > 3) valid = false;
        }
        if (!valid) continue;
        QVariantMap item;
        item.insert("deckId", QStringLiteral("deck%1").arg(index));
        item.insert("name", QStringLiteral("Deck %1").arg(index));
        item.insert("characters", characters.toVariantList());
        item.insert("cards", cards.toVariantList());
        m_validDecks.append(item);
    }
    emit validDecksChanged();
}

QStringList DeckManager::cards() const
{
    return m_cards;
}

QStringList DeckManager::characters() const
{
    return m_characters;
}

void DeckManager::changeDeckIndex(int val)
{
    deckIdx += val;
    if (3 < deckIdx || deckIdx < 1) {
        deckIdx -= val;
    }

    emit deckIndexChanged();
}

bool DeckManager::addCharacter(const QString &cardId, const QString& username)
{
    qDebug() << ' ' << cardId << '\n';
    if (cardId.isEmpty())
        return false;

    if (m_characters.size() >= 3) {
        qDebug() << "limit reached";
        emit errorOccurred(QStringLiteral("Maximum 3 characters allowed"));
        return false;
    }

    if (m_characters.count(cardId)){
        qDebug() << "Duplicate characters";
        emit errorOccurred(QStringLiteral("These characters have no twin"));
        return false;
    }

    m_characters.append(cardId);
    std::sort(m_characters.begin(), m_characters.end());
    emit charactersChanged();
    emit deckChanged();
    saveDeck(username);
    return true;
}

bool DeckManager::removeCharacter(const QString &cardId, const QString& username)
{
    if (!m_characters.contains(cardId))
        return false;

    m_characters.removeOne(cardId);
    emit charactersChanged();
    emit deckChanged();
    saveDeck(username);
    return true;
}

bool DeckManager::addCard(const QString &cardId, const QString& username)
{
    if (cardId.isEmpty())
        return false;

    if (m_cards.size() >= 30) {
        emit errorOccurred(QStringLiteral("Maximum 30 cards allowed"));
        return false;
    }

    if(m_cards.count(cardId) >= 3) {
        emit errorOccurred(QStringLiteral("Maximum 3 copies of a card allowed"));
        return false;
    }

    m_cards.append(cardId);

    std::sort(m_cards.begin(), m_cards.end());

    emit cardsChanged();
    emit deckChanged();

    saveDeck(username);

    return true;
}

bool DeckManager::removeCard(const QString &cardId, const QString& username)
{
    if (!m_cards.contains(cardId))
        return false;

    m_cards.removeOne(cardId);
    emit cardsChanged();
    emit deckChanged();
    saveDeck(username);
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

void DeckManager::saveDeck(const QString& username)
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

    QSqlDatabase db = QSqlDatabase::database(DB_CONN_NAME);

    if (!db.isOpen() && !db.open()) {
        qDebug() << "Database connection failed in saveDeck:" << db.lastError().text();
        return;
    }

    const QString cleanUser = username;
    qDebug() << username;
    QJsonDocument doc(root);
    QString newDeckJsonString = doc.toJson(QJsonDocument::Compact);

    QSqlQuery query(db);
    query.prepare(
        "UPDATE users "
        "SET decks = json_set(decks, :deckPath, json(:deckJson)) "
        "WHERE username = :user"
    );
    query.bindValue(QStringLiteral(":user"), cleanUser);
    query.bindValue(QStringLiteral(":deckJson"), newDeckJsonString);

    if (deckIdx == 1) {
        query.bindValue(QStringLiteral(":deckPath"), "$.deck1");
    } else if (deckIdx == 2) {
        query.bindValue(QStringLiteral(":deckPath"), "$.deck2");
    } else {
        query.bindValue(QStringLiteral(":deckPath"), "$.deck3");
    }

    if (!query.exec()) {
        qDebug() << "SQL Save Deck Error:" << query.lastError().text();
    } else {
        qDebug() << "Successfully saved deck" << deckIdx << "for user:" << cleanUser;
    }

}

void DeckManager::loadDeck(const QString& username)
{
    QSqlDatabase db = QSqlDatabase::database(DB_CONN_NAME);

    if (!db.isOpen() && !db.open()) {
        qDebug() << "Database connection failed in loadDeck:" << db.lastError().text();
        return;
    }

    const QString cleanUser = username;
    QSqlQuery query(db);

    query.prepare(
        "SELECT json_extract(decks, :deckPath) FROM users WHERE username = :user"
    );
    query.bindValue(QStringLiteral(":user"), cleanUser);

    if (deckIdx == 1) {
        query.bindValue(QStringLiteral(":deckPath"), "$.deck1");
    } else if (deckIdx == 2) {
        query.bindValue(QStringLiteral(":deckPath"), "$.deck2");
    } else {
        query.bindValue(QStringLiteral(":deckPath"), "$.deck3");
    }

    if (!query.exec() || !query.next()) {
        qDebug() << "Deck fetch failed or no user found:" << query.lastError().text();
        return;
    }

    QString jsonString = query.value(0).toString();

    if (jsonString.isEmpty() || jsonString == "null") {
        jsonString = "{\"characters\":[],\"cards\":[]}";
    }

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
