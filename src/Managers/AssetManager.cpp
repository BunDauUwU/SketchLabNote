#include "AssetManager.h"
#include "../Data/AssetResolver.h"

AssetManager::AssetManager(QObject *parent) : QObject(parent) {}

QString AssetManager::resolveCardImage(const QString &data)
{
    return AssetResolver::resolveCardImage(data);
}

QString AssetManager::resolveCharacterImage(const QString &data)
{
    return AssetResolver::resolveCharacterImage(data);
}

QString AssetManager::resolveEffectImage(const QString &name, const QString &kind, const QString &icon)
{
    return AssetResolver::resolveEffectImage(name, kind, icon);
}

QString AssetManager::resolveElementImage(const QString &element)
{
    return AssetResolver::resolveElementImage(element);
}
