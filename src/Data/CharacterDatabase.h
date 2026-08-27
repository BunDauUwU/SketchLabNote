#pragma once

#include <QObject>
#include <QUrl>
#include <QJsonObject>
#include <QProperty>
#include <QWebSocket>
#include <QVariantList>
#include <QVariantMap>

class CharacterDataBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList characterList READ characterList NOTIFY characterListChanged)

public:
    explicit CharacterDataBase(QObject *parent = nullptr);
    QStringList characterList() const;

    Q_INVOKABLE QString name(const int index);
    Q_INVOKABLE QString skills(const int index);
    Q_INVOKABLE QVariantList skillList(const QString& characterId) const;
    Q_INVOKABLE QVariantMap details(const QString& characterId) const;
    Q_INVOKABLE void handlecharacterClick(int index);

signals:
    void charSelected(const QString &charId);
    void characterListChanged();

private:
    QStringList m_characterList;
    QStringList m_characterName;
    QJsonObject m_characterInfo;
};
