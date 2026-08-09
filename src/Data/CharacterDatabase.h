#pragma once

#include <QObject>
#include <QUrl>
#include <QJsonObject>
#include <QProperty>
#include <QWebSocket>

class CharacterDataBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList characterList READ characterList NOTIFY characterListChanged)

public:
    explicit CharacterDataBase(QObject *parent = nullptr);
    QStringList characterList() const;

    Q_INVOKABLE void handlecharacterClick(int index);

signals:
    void charSelected(const QString &charId);
    void characterListChanged();

private:
    QStringList m_characterList;
};
