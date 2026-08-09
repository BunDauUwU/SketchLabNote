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

    // for (int i = 0; i < m_characterList.size(); ++i) {
    //     qDebug() << QString("[%1] -> %2").arg(i).arg(m_characterList.at(i));
    // }
    // qDebug() << "========================================";
}

QStringList CharacterDataBase::characterList() const
{
    return m_characterList;
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

