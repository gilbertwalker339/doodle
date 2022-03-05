#include "lobbyhandler.h"

LobbyHandler::LobbyHandler(QObject *parent)
    : QObject{parent}
{

}

LobbyHandler::~LobbyHandler()
{

}

void LobbyHandler::addClientId(QString clientId)
{
    if(!m_clientMap.keys().contains(clientId)) {
         setClientIdReady(clientId, false);
    }
    resetReadyLobby();
}

void LobbyHandler::setLobbyId(QString id)
{
    m_lobbyId = id;
}

QStringList LobbyHandler::clientIdList()
{
    return m_clientMap.keys();
}

void LobbyHandler::setClientIdReady(const QString &clientId, bool isReady)
{
    m_clientMap[clientId] = isReady;
}

QStringList LobbyHandler::clientIdReadyList()
{
    QStringList list;

    for(const QString& clientId : m_clientMap.keys()) {
        if(m_clientMap[clientId] == true) {
            list.append(clientId);
        }
    }

    return list;
}

bool LobbyHandler::isClientsInLobbyReady()
{
    bool isReady = true;
    QStringList readyList = clientIdReadyList();
    for(const QString& clientId : m_clientMap.keys()) {
         isReady = isReady && m_clientMap[clientId];
    }
    return (isReady && readyList.count() == m_clientMap.keys().count());
}

void LobbyHandler::resetReadyLobby()
{
    for(const QString& clientId : m_clientMap.keys()) {
        m_clientMap[clientId] = false;
    }
}

QMap<QString, QString> LobbyHandler::clientImageMap()
{
    return m_clientImageMap;
}

void LobbyHandler::drawnRequest(const QString& type, const QString& clientId, const QString& hexData)
{
    m_clientImageMap[clientId] = hexData;
    setClientIdReady(clientId, true);

    if(isClientsInLobbyReady()) {
        if(type == "scribbleData") emit scribblesReady(chooseObjectToDraw());
        else if(type == "takeawayData") emit takeawayReady();
    }
}

void LobbyHandler::voteRequest(const QString& clientId)
{
    if(m_voteMap.keys().contains(clientId)) m_voteMap[clientId]++;
    else m_voteMap[clientId] = 1;
    int totalVote = 0;
    for(const int& vote : m_voteMap.values()) {
        totalVote += vote;
    }

    if(totalVote == m_clientMap.count()) {
        emit gameOverReady();
    }
}

QString LobbyHandler::chooseObjectToDraw()
{
    QStringList objects = QStringList() << "car" << "bicycle" << "motor" << "computer" << "exploit";
    std::random_device rd;
    std::default_random_engine engine;
    engine.seed(rd());
    std::uniform_int_distribution<int> dist(0, objects.length());
    return objects[dist(engine)];
}

QString LobbyHandler::highestVote()
{
    QString highestClient = QString();
    int highest = 0;
    for(const QString& clientId : m_voteMap.keys()) {
        if(m_voteMap[clientId] > highest) {
            highest = m_voteMap[clientId];
            highestClient = clientId;
        }
    }

    return highestClient;
}


