#include "CardDatabase.h"
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>

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

    // for (int i = 0; i < m_cardList.size(); ++i) {
    //     qDebug() << QString("[%1] -> %2").arg(i).arg(m_cardList.at(i));
    // }
    // qDebug() << "========================================";
}

QStringList CardDatabase::cardList() const
{
    return m_cardList;
}

void CardDatabase::handlecardClick(int index)
{
    if (index < 0 || index >= m_cardList.size())
        return;

    const QString source = m_cardList.at(index);

    QFileInfo fileInfo(source);

    QString cardId = fileInfo.completeBaseName();

    qDebug() << "Card selected:"
             << cardId
             << source;

    emit cardSelected(cardId);
}

