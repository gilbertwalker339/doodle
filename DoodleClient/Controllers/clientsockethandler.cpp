#include "clientsockethandler.h"

ClientSocketHandler::ClientSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_client = new QWebSocket();
    connect(m_client, &QWebSocket::connected, this, &ClientSocketHandler::connected);
    connect(m_client, &QWebSocket::disconnected, this, &ClientSocketHandler::disconnected);
    connect(m_client, &QWebSocket::textMessageReceived, this, &ClientSocketHandler::textMessageFollowing);
}

ClientSocketHandler::~ClientSocketHandler()
{
    m_client->close();
    m_client->deleteLater();
}

void ClientSocketHandler::connectToHost(const QString& url)
{
    m_client->open(url);
}

void ClientSocketHandler::sendTextMessageToServer(const QString &message)
{
    m_client->sendTextMessage(message);
}

void ClientSocketHandler::connected()
{
    qDebug() << "client is running";
}

void ClientSocketHandler::disconnected()
{
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if(client) {
        client->close();
        client->deleteLater();
    }
}

void ClientSocketHandler::textMessageReceived(const QString &message)
{
    emit textMessageFollowing(message);
}
