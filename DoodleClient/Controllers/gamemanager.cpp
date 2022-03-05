#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}, m_lobbyId(QString()), m_clientId(QString()), m_objectDraw(QString()), m_scribblePath(QString()),
      m_imagePathList(QStringList()), m_clientIdInLobby(QStringList()), m__clientIdReady(QStringList())
{
    m_client = new ClientSocketHandler(this);
    m_message = new MessageHandler(this);

    connect(m_client, &ClientSocketHandler::textMessageFollowing, m_message, &MessageHandler::textMessageReceived);
    connect(m_message, &MessageHandler::registerId, this, &GameManager::registerId);
    connect(m_message, &MessageHandler::joinLobby, this, &GameManager::joinLobby);
    connect(m_message, &MessageHandler::failedLobby, this, &GameManager::failedLobby);
    connect(m_message, &MessageHandler::updateClientInLobby, this, &GameManager::setClientIdInLobby);
    connect(m_message, &MessageHandler::messageChatReceived, this, &GameManager::messageChatReceived);
    connect(m_message, &MessageHandler::readyLobbyReceived, this, &GameManager::readyLobbyReceived);
    connect(m_message, &MessageHandler::updateClientReady, this, &GameManager::updateClientReady);
    connect(m_message, &MessageHandler::readyScribbleReceived, this, &GameManager::readyScribbleReceived);
    connect(m_message, &MessageHandler::readyTakeawayReceived, this, &GameManager::readyTakeawayReceived);
    connect(m_message, &MessageHandler::readyGameOverReceived, this, &GameManager::readyGameOverReceived);
}

GameManager::~GameManager()
{
    m_client->deleteLater();
    m_message->deleteLater();
}

void GameManager::connectToHost(const QString &url)
{
    m_client->connectToHost(url);
}

void GameManager::createGameRequest()
{
    m_client->sendTextMessageToServer("type:createGame;payload:0;sender:" + m_clientId);
}

void GameManager::joinGameRequest(QString lobbyId)
{
    m_client->sendTextMessageToServer("type:joinGame;payload:" + lobbyId + ";sender:" + m_clientId);
}

void GameManager::sendMessageRequest(QString message)
{
    m_client->sendTextMessageToServer("type:message;payload:" + m_lobbyId + ";message:" + message + ";sender:" + m_clientId);
}

void GameManager::readyRequest()
{
    m_client->sendTextMessageToServer("type:readyLobby;payload:" + m_lobbyId + ";sender:" + m_clientId);
}

void GameManager::drawnRequest()
{
    QFile file("temp.png");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }
    QByteArray buffer = file.readAll();
    file.close();

    if(m_objectDraw == QString()) {
        m_client->sendTextMessageToServer("type:scribbleData;payload:" + buffer.toHex() + ";sender:" + m_clientId);
    }
    else {
        m_client->sendTextMessageToServer("type:takeawayData;payload:" + buffer.toHex() + ";sender:" + m_clientId);
    }
}

void GameManager::voteRequest(QString imagePath)
{
    QFileInfo file(imagePath);
    QString voteClientId = file.baseName();

    m_client->sendTextMessageToServer("type:vote;payload:" + voteClientId + ";sender:" + m_clientId);
}

QString GameManager::bestImagePath()
{
    QString path = QDir::currentPath() + QDir::separator() + "temp" + QDir::separator() + m_highestClientId + ".png";
    return path;
}

void GameManager::registerId(QString id)
{
    m_clientId = id;
}

void GameManager::joinLobby(QString id, QStringList clientIdList)
{
    m_lobbyId = id;
    setClientIdInLobby(clientIdList);
    emit createGameFinished();
}

void GameManager::readyScribbleReceived(const QString &objectDraw, const QString &hexData)
{
    setObjectDraw(objectDraw);

    QString imagePath = m_clientId + ".png";
    QFile file(imagePath);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return;
    }
    QByteArray buffer = QByteArray::fromHex(hexData.toLocal8Bit());
    file.write(buffer);
    file.flush();
    file.close();

    setScribblePath(imagePath);

    emit nextToTakeway();
}

void GameManager::readyTakeawayReceived(QMap<QString, QString> clientImageMap)
{
   QDir currentDir = QDir::currentPath();
   currentDir.mkdir("temp");
   QString currentPath = QDir::currentPath() + QDir::separator() + "temp" + QDir::separator();
   QStringList imagePathList;
   for(const QString& clientId : clientImageMap.keys()) {
       QString imagePath = currentPath + clientId + ".png";
       QFile file(imagePath);
       if(!file.open(QIODevice::WriteOnly)) {
           qDebug() << file.errorString();
           return;
       }
       QByteArray buffer = QByteArray::fromHex(clientImageMap[clientId].toLocal8Bit());
       file.write(buffer);
       file.flush();
       file.close();

       imagePathList.append(imagePath);
   }

   setImagePathList(imagePathList);

   emit nextToVote();
}

QString GameManager::lobbyId() const
{
    return m_lobbyId;
}

void GameManager::setLobbyId(QString lobbyId)
{
    m_lobbyId = lobbyId;
    emit lobbyIdChanged();
}

QStringList GameManager::clientIdInLobby() const
{
    return m_clientIdInLobby;
}

void GameManager::setClientIdInLobby(QStringList clientIdList)
{
    if(m_clientIdInLobby != clientIdList) {
        m_clientIdInLobby = clientIdList;
        emit clientIdInLobbyChanged();
    }
}

QString GameManager::objectDraw()
{
    return m_objectDraw;
}

void GameManager::setObjectDraw(QString objectDraw)
{
    m_objectDraw = objectDraw;
    emit objectDrawChanged();
}

QString GameManager::scribblePath()
{
    QString path = "file://" + QDir::currentPath() + QDir::separator() + m_scribblePath;
    return path;
}

void GameManager::setScribblePath(QString path)
{
    m_scribblePath = path;
    emit scribblePathChanged();
}

QStringList GameManager::imagePathList()
{
    return m_imagePathList;
}

void GameManager::setImagePathList(QStringList imagePathList)
{
    if(m_imagePathList != imagePathList) {
        m_imagePathList = imagePathList;
        emit imagePathListChanged();
    }
}

QString GameManager::bestClientId()
{
    return m_highestClientId;
}

void GameManager::setBestClientId(QString clientId)
{
    if(m_highestClientId != clientId) {
        m_highestClientId = clientId;
        emit bestClientIdChanged();
    }
}
