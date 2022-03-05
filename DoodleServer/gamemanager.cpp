#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_server = new ServerSocketHandler(this);
    m_message = new MessageHandler(this);

    connect(m_server, &ServerSocketHandler::textMessageFollowing, m_message, &MessageHandler::textMessageReceived);
    connect(m_message, &MessageHandler::createGameRequest, this, &GameManager::createGameRequest);
    connect(m_message, &MessageHandler::joinGameRequest, this, &GameManager::joinGameRequest);
    connect(m_message, &MessageHandler::messageRequest, this, &GameManager::messageRequest);
    connect(m_message, &MessageHandler::readyLobby, this, &GameManager::readyLobby);
}

GameManager::~GameManager()
{
    m_server->deleteLater();
    m_message->deleteLater();
}

void GameManager::createGameRequest(const QString &clientId)
{
    LobbyHandler* newLobby = new LobbyHandler(this);

    connect(m_message, &MessageHandler::drawnRequest, newLobby, &LobbyHandler::drawnRequest);
    connect(newLobby, &LobbyHandler::scribblesReady, this, &GameManager::scribblesReady);
    connect(newLobby, &LobbyHandler::takeawayReady, this, &GameManager::takeawayReady);
    connect(m_message, &MessageHandler::voteRequest, newLobby, &LobbyHandler::voteRequest);
    connect(newLobby, &LobbyHandler::gameOverReady, this, &GameManager::gameOverReady);

    newLobby->addClientId(clientId);

    int id = 0;
    while(true) {
        id = QRandomGenerator::global()->bounded(1000, 9999);
        if(!m_lobbyMap.keys().contains(QString::number(id))) {
            newLobby->setLobbyId(QString::number(id));
            break;
        }
    }
    m_lobbyMap[QString::number(id)] = newLobby;

    m_server->sendTextMessageToClient(clientId,  "type:createGame;payload:" + QString::number(id) + ";clientList:" + newLobby->clientIdList().join(','));
}

void GameManager::joinGameRequest(const QString &clientId, const QString &lobbyId)
{
    if(m_lobbyMap.keys().contains(lobbyId)) {
        LobbyHandler* lobby = m_lobbyMap[lobbyId];
        lobby->addClientId(clientId);
        m_server->sendTextMessageToClient(clientId, "type:joinGame;payload:" + lobbyId + ";clientList:" + lobby->clientIdList().join(','));
        m_server->sendTextMessageToClientList(lobby->clientIdList(), "type:updateClientInLobby;payload:" + lobby->clientIdList().join(','));
    }
    else {
        m_server->sendTextMessageToClient(clientId, "type:failGame");
    }
}

void GameManager::messageRequest(const QString &clientId, const QString &lobbyId, const QString &message)
{
    if(m_lobbyMap.keys().contains(lobbyId)) {
        LobbyHandler* lobby = m_lobbyMap[lobbyId];
        m_server->sendTextMessageToClientList(lobby->clientIdList(), "type:message;payload:" + message + ";sender:" + clientId);
    }
}

void GameManager::readyLobby(const QString &clientId, const QString &lobbyId)
{
    if(m_lobbyMap.keys().contains(lobbyId)) {
        LobbyHandler* lobby = m_lobbyMap[lobbyId];
        lobby->setClientIdReady(clientId, true);

        if(lobby->isClientsInLobbyReady()) {
            lobby->resetReadyLobby();

            m_server->sendTextMessageToClientList(lobby->clientIdList(), "type:readyLobby");
        }
        else {
            m_server->sendTextMessageToClientList(lobby->clientIdList(), "type:updateClientReady;payload:" + lobby->clientIdReadyList().join(','));
        }

    }
}

void GameManager::scribblesReady(const QString &objectDraw)
{
    LobbyHandler* lobby = qobject_cast<LobbyHandler*>(sender());

    QStringList clientIdList = lobby->clientIdList();
    QMap<QString, QString> clientImageMap = lobby->clientImageMap();
    QString clientId = QString();
    QString imageData = QString();
    for(int i = 0; i < clientIdList.count(); i++) {
        clientId = clientIdList[i];
        if(i + 1 == clientImageMap.count()) {
            imageData = clientImageMap[clientIdList[0]];
        }
        else {
            imageData = clientImageMap[clientIdList[i + 1]];
        }
        m_server->sendTextMessageToClient(clientIdList[i], "type:readyScribble;payload:" + imageData + ";objectDraw:" + objectDraw);
    }

    lobby->resetReadyLobby();
}

void GameManager::takeawayReady()
{
    LobbyHandler* lobby = qobject_cast<LobbyHandler*>(sender());
    QMap<QString, QString> clientImageMap = lobby->clientImageMap();
    m_server->sendTextMessageToClientList(clientImageMap.keys(), "type:readyTakeaway;payload:" + clientImageMap.keys().join(',') + ";images:" + clientImageMap.values().join(','));

    lobby->resetReadyLobby();
}

void GameManager::gameOverReady()
{
    LobbyHandler* lobby = qobject_cast<LobbyHandler*>(sender());
    QString highestClientId = lobby->highestVote();
    m_server->sendTextMessageToClientList(lobby->clientIdList(), "type:readyGameOver;payload:" + highestClientId);
}
