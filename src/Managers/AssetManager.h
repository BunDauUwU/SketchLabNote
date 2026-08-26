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
private:
    QStringList m_cards;
    QStringList m_characters;
    int deckIdx = 1;
    int selectedCharacter = 1;

};