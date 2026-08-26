#include "CardDatabase.h"
#include <QDirIterator>
#include <QUrl>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QRegularExpression>

CardDatabase::CardDatabase(QObject *parent) : QObject(parent)
{
    QDirIterator it(":", QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString resourcePath = it.next();
        QFileInfo fileInfo(resourcePath);


        if (resourcePath.contains("/assets/cards") && fileInfo.isFile())
        {
            QString ext = fileInfo.suffix().toLower();
            if (ext == "png" || ext == "jpg" || ext == "jpeg")
            {
                QString qrcUrl = resourcePath;
                if (qrcUrl.startsWith(":")) {
                    qrcUrl.replace(0, 1, "qrc:");
                }

                m_cardList.append(qrcUrl);
            }
        }
    }

    qDebug() << "========================================";
    qDebug() << "QUÉT RESOURCE THÀNH CÔNG! ĐÃ TÌM THẤY:" << m_cardList.size() << "cardS.";

    std::sort(m_cardList.begin(), m_cardList.end());

    for (auto source : m_cardList) {
        QFileInfo fileInfo(source);
        QString cardId = fileInfo.completeBaseName();
        m_cardName.append(cardId);
    }

    QString filePath = ":/lumieTcg/json/card.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cant read card.json" << filePath;
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

    m_cardInfo = rootObj["standard"].toObject();
}

QStringList CardDatabase::cardList() const
{
    return m_cardList;
}

QString CardDatabase::name (const int index) {
    QString name = m_cardName.at(index);
    return name;
}

QString CardDatabase::skills(const int index) {
    QString name = m_cardName.at(index);
    QJsonDocument doc(m_cardInfo);
    QString indentedString = doc.toJson();
    return indentedString;
}

int CardDatabase::cost(const QString& cardId) const
{
    QString normalizedId = cardId;
    normalizedId.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
    for (auto it = m_cardInfo.constBegin(); it != m_cardInfo.constEnd(); ++it) {
        QString candidate = it.key();
        candidate.remove(QRegularExpression(QStringLiteral("[^A-Za-z0-9]")));
        if (candidate.compare(normalizedId, Qt::CaseInsensitive) != 0) continue;
        int total = 0;
        const QJsonObject costs = it.value().toObject().value("cost").toObject();
        for (auto cost = costs.constBegin(); cost != costs.constEnd(); ++cost) {
            if (cost.key() != "ENERGY") total += cost.value().toInt();
        }
        return total;
    }
    return 0;
}

void CardDatabase::handlecardClick(int index)
{
    if (index < 0 || index >= m_cardList.size())
        return;

    const QString source = m_cardList.at(index);
    const QString cardId = m_cardName.at(index);

    qDebug() << "Card selected:"
             << cardId
             << source;

    emit cardSelected(cardId);
}
