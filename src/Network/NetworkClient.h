// src/Network/NetworkClient.h
#pragma once

#include <QObject>
#include <QUrl>
#include <QJsonObject>
#include <QWebSocket>

class NetworkClient : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit NetworkClient(QObject* parent = nullptr);

    bool isConnected() const;
    QString lastError() const;

    Q_INVOKABLE void connectToServer(const QString& url);
    Q_INVOKABLE void disconnectFromServer();

    void sendMessage(const QJsonObject& message);

signals:
    void connectedChanged();
    void lastErrorChanged();

    void connected();
    void disconnected();
    void messageReceived(const QJsonObject& message);
    void errorOccurred(const QString& error);

private slots:
    void handleConnected();
    void handleDisconnected();
    void handleTextMessageReceived(const QString& message);
    void handleErrorOccurred(QAbstractSocket::SocketError error);

private:
    void setLastError(const QString& error);

private:
    QWebSocket m_socket;
    bool m_connected = false;
    QString m_lastError;
};