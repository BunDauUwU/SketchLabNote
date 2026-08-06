#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/Network/NetworkClient.h"
#include "src/Managers/MatchmakingManager.h"
#include "src/Managers/GameManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    NetworkClient networkClient;

    MatchmakingManager matchmakingManager;
    matchmakingManager.setNetworkClient(&networkClient);

    GameManager gameManager;
    gameManager.setNetworkClient(&networkClient);

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
        &matchmakingManager,
        &MatchmakingManager::matchFound,
        &gameManager,
        &GameManager::setMatchInfo
        );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("networkClient", &networkClient);
    engine.rootContext()->setContextProperty("matchmakingManager", &matchmakingManager);
    engine.rootContext()->setContextProperty("gameManager", &gameManager);

    networkClient.connectToServer("ws://127.0.0.1:8080");
    //const QUrl url(QStringLiteral("qrc:/qml/App.qml"));
    engine.loadFromModule("lumieTcg", "App");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}