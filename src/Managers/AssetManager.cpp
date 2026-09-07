#include "AssetManager.h"

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

//resolveCharacterImage
//resolveCardImage

AssetManager::AssetManager(QObject *parent) : QObject(parent) {

}

QString AssetManager::resolveCardImage(const QString &data)
{
    QString filePath = ":/lumieTcg/assets/cards/";
    filePath += data;
    return filePath;
}

QString AssetManager::resolveCharacterImage(const QString &data)
{
    QString filePath = ":/lumieTcg/assets/characters/";
    filePath += data;
    return filePath;
}