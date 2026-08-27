#include "CharacterDatabase.h"
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>

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

QVariantList CharacterDataBase::skillList(const QString& characterId) const
{
    QVariantList result;
    QString dataId = QFileInfo(characterId).baseName();
    QString normalizedId = QFileInfo(characterId).baseName();
    normalizedId.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
    for (auto it = m_characterInfo.constBegin(); it != m_characterInfo.constEnd(); ++it) {
        QString candidate = it.key();
        candidate.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
        if (candidate.compare(normalizedId, Qt::CaseInsensitive) == 0) { dataId = it.key(); break; }
    }
    const QJsonObject skills = m_characterInfo.value(dataId).toObject().value("skills").toObject();
    for (auto it = skills.constBegin(); it != skills.constEnd(); ++it) {
        const QJsonObject data = it.value().toObject();
        const QJsonObject costs = data.value("cost").toObject();
        int elementPointCost = 0;
        for (auto cost = costs.constBegin(); cost != costs.constEnd(); ++cost) {
            if (cost.key() != "ENERGY") elementPointCost += cost.value().toInt();
        }
        QVariantMap skill;
        const QJsonObject damage = data.value("damage").toObject();
        int damageValue = 0;
        QString element = QStringLiteral("Physical");
        for (auto hit = damage.constBegin(); hit != damage.constEnd(); ++hit) {
            damageValue += hit.value().toInt();
            if (hit.key() != "PHYSICAL" && hit.key() != "PIERCE") element = hit.key();
        }
        skill.insert("name", it.key());
        skill.insert("cost", elementPointCost);
        skill.insert("hpDelta", -damageValue);
        skill.insert("energyDelta", data.value("type").toArray().contains(QJsonValue(QStringLiteral("Elemental Burst"))) ? 0 : 1);
        skill.insert("element", element);
        skill.insert("description", QString::fromUtf8(QJsonDocument(data).toJson(QJsonDocument::Compact)));
        result.append(skill);
    }
    return result;
}

QVariantMap CharacterDataBase::details(const QString& characterId) const
{
    QString normalizedId = characterId;
    normalizedId.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
    for (auto it = m_characterInfo.constBegin(); it != m_characterInfo.constEnd(); ++it) {
        QString candidate = it.key();
        candidate.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
        if (candidate.compare(normalizedId, Qt::CaseInsensitive) != 0) continue;
        QVariantMap result = it.value().toObject().toVariantMap();
        result.insert("name", it.key());
        result.insert("skillList", skillList(characterId));
        return result;
    }
    return {{"name", characterId}};
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
