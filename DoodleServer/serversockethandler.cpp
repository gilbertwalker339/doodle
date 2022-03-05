#include "serversockethandler.h"

ServerSocketHandler::ServerSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_server = new QWebSocketServer("DoodleServer", QWebSocketServer::NonSecureMode, this);
    connect(m_server, &QWebSocketServer::newConnection, this, &ServerSocketHandler::newConnection);

    if(!m_server->listen(QHostAddress::Any, 2048)) {
        qDebug() << m_server->errorString();
        return;
    }

    qDebug() << "server is running";
}

ServerSocketHandler::~ServerSocketHandler()
{
    m_server->close();
    m_server->deleteLater();
}

void ServerSocketHandler::sendTextMessageToClient(const QString &clientId, const QString &message)
{
    QWebSocket* client = m_clientMap[clientId];
    if(client) {
        client->sendTextMessage(message);
    }
}

void ServerSocketHandler::sendTextMessageToClientList(const QStringList &clientIdList, const QString &message)
{
    for(const QString& clientId : clientIdList) {
        sendTextMessageToClient(clientId, message);
    }
}

void ServerSocketHandler::newConnection()
{
    QWebSocket* client = m_server->nextPendingConnection();
    client->setParent(this);
    if(client) {
        connect(client, &QWebSocket::textMessageReceived, this, &ServerSocketHandler::textMessageReceived);
        connect(client, &QWebSocket::disconnected, this, &ServerSocketHandler::disconnected);

        int id = 0;
        while(true) {
            id = QRandomGenerator::global()->bounded(1000, 9999);
            if(!m_clientMap.keys().contains(QString::number(id))) {
                m_clientMap[QString::number(id)] = client;
                break;
            }
        }

        client->sendTextMessage("type:uniqueId;payload:" + QString::number(id));
    }
}

void ServerSocketHandler::textMessageReceived(const QString &message)
{
    emit textMessageFollowing(message);
}

void ServerSocketHandler::disconnected()
{
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());
    if(client) {
        for(QMap<QString, QWebSocket*>::iterator clientIterator = m_clientMap.begin();
            clientIterator != m_clientMap.end(); clientIterator++) {
            if(clientIterator.value() == client) {
                m_clientMap.remove(clientIterator.key());
                break;;
            }
        }
        client->deleteLater();
    }
}
