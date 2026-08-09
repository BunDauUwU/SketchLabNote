#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/Network/NetworkClient.h"
#include "src/Managers/MatchmakingManager.h"
#include "src/Managers/GameManager.h"
#include "src/Managers/AuthManager.h"
#include "src/Managers/DeckManager.h"
#include "src/Data/CharacterDatabase.h"
#include "src/Data/CardDatabase.h"
#include "src/Data/AssetResolver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    NetworkClient networkClient;

    MatchmakingManager matchmakingManager;
    matchmakingManager.setNetworkClient(&networkClient);

    GameManager gameManager;
    gameManager.setNetworkClient(&networkClient);

    AuthManager authManager;
    authManager.setNetworkClient(&networkClient);

    DeckManager deckManager;

    AssetResolver assetResolver;

    QObject::connect(
        &networkClient,
        &NetworkClient::messageReceived,
        &matchmakingManager,
        &MatchmakingManager::handleServerMessage
        );

    QObject::connect(
        &networkClient,
        &NetworkClient::messageReceived,
        &gameManager,
        &GameManager::handleServerMessage
        );

    QObject::connect(
        &networkClient,
        &NetworkClient::messageReceived,
        &authManager,
        &AuthManager::handleServerMessage
        );

    QObject::connect(
        &matchmakingManager,
        &MatchmakingManager::matchFound,
        &gameManager,
        &GameManager::setMatchInfo
        );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("networkClient", &networkClient);
    engine.rootContext()->setContextProperty("matchmakingManager", &matchmakingManager);
    engine.rootContext()->setContextProperty("gameManager", &gameManager);
    engine.rootContext()->setContextProperty("authManager", &authManager);
    engine.rootContext()->setContextProperty("deckManager", &deckManager);
    engine.rootContext()->setContextProperty("assetResolver", &assetResolver);

    // Network
    networkClient.connectToServer("ws://127.0.0.1:8080");

    // Deck
    CharacterDataBase characterDataBase;
    engine.rootContext()->setContextProperty("charDataBase", &characterDataBase);
    CardDatabase cardDataBase;
    engine.rootContext()->setContextProperty("cardDataBase", &cardDataBase);




    // U know what is this
    engine.loadFromModule("lumieTcg", "App");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}