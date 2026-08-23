#include "CharacterDatabase.h"
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>

CharacterDataBase::CharacterDataBase(QObject *parent) : QObject(parent)
{
    QDirIterator it(":", QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString resourcePath = it.next();
        QFileInfo fileInfo(resourcePath);

        if (resourcePath.contains("/assets/characters/") && fileInfo.isFile())
        {
            QString ext = fileInfo.suffix().toLower();
            if (ext == "png" || ext == "jpg" || ext == "jpeg")
            {
                QString qrcUrl = resourcePath;
                if (qrcUrl.startsWith(":")) {
                    qrcUrl.replace(0, 1, "qrc:");
                }

                m_characterList.append(qrcUrl);
            }
        }
    }

    qDebug() << "========================================";
    qDebug() << "QUÉT RESOURCE THÀNH CÔNG! ĐÃ TÌM THẤY:" << m_characterList.size() << "CHARACTERS.";

    for (auto source : m_characterList) {
        QFileInfo fileInfo(source);
        QString characterId = fileInfo.completeBaseName();
        m_characterName.append(characterId);
    }

    QString filePath = ":/lumieTcg/json/character.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cant read character.json" << filePath;
        return ;
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Lỗi cấu trúc JSON:" << error.errorString();
        return ;
    }

    QJsonObject rootObj = jsonDoc.object();

    m_characterInfo = rootObj["standard"].toObject();
}

QStringList CharacterDataBase::characterList() const
{
    return m_characterList;
}

QString CharacterDataBase::name (const int index) {
    QString name = m_characterName.at(index);
    return name;
}

QString CharacterDataBase::skills(const int index) {
    QString name = m_characterName.at(index);
    QJsonDocument doc(m_characterInfo[name].toObject());
    QString indentedString = doc.toJson(QJsonDocument::Indented);
    return indentedString;
}

void CharacterDataBase::handlecharacterClick(int index)
{
    if (index < 0 || index >= m_characterList.size())
        return;

    const QString source = m_characterList.at(index);

    QFileInfo fileInfo(source);

    QString charId = fileInfo.completeBaseName();

    qDebug() << "Card selected:"
             << charId
             << source;

    emit charSelected(charId);
}

