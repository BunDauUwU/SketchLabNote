#pragma once

#include <QObject>
#include <QStringList>
#include <QVariantList>

#include <QObject>

class AssetManager : public QObject
{
    Q_OBJECT

public:
    explicit AssetManager(QObject *parent = nullptr);

    Q_INVOKABLE QString resolveCardImage(const QString &data);
    Q_INVOKABLE QString resolveCharacterImage(const QString &data);
private:


};