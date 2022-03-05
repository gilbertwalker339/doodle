#include "messagehandler.h"

MessageHandler::MessageHandler(QObject *parent)
    : QObject{parent}
{

}

MessageHandler::~MessageHandler()
{

}

void MessageHandler::textMessageReceived(const QString &message)
{
    //type:uniqueId;payload:123
    //type:createGame:payload:456;clientList:111,222,333
    //type:joinGame;payload:456;clientList:111,222,333
    //type:failGame
    //type:updateClientInLobby;payload:111,222,333
    //type:message;payload:Hello;sender:123
    //type:readyLobby
    //type:updateClientReady;payload:111,222,333
    //type:readyScribble;payload:0x123456789;objectDraw:car
    //type:readyTakeaway;payload:111,222,333;images:0x111,0x222,0x333
    //type:readyGameOver;payload:123

    QStringList separated = message.split(QRegularExpression(";"));

    if(separated.first() == "type:uniqueId") {
        QString id = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            id = separated.first().remove("payload:");
        }
        if(id != QString()) {
            emit registerId(id);
        }
    }
    //type:createGame:payload:456;clientList:111,222,333
    //type:joinGame;payload:456;clientList:111,222,333
    else if(separated.first() == "type:createGame" || separated.first() == "type:joinGame") {
        QString lobbyId = QString();
        QStringList clientIdList = QStringList();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            lobbyId = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("clientList:")) {
            clientIdList = separated.first().remove("clientList:").split(QRegularExpression(","));
        }
        if(lobbyId != QString() && clientIdList != QStringList()) {
            emit joinLobby(lobbyId, clientIdList);
        }
    }
    else if(separated.first() == "type:failGame") {
        emit failedLobby();
    }
    //type:updateClientInLobby;payload:111,222,333
    else if(separated.first() == "type:updateClientInLobby") {
        QStringList clientIdList = QStringList();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            clientIdList = separated.first().remove("payload:").split(QRegularExpression(","));
            emit updateClientInLobby(clientIdList);
        }
    }
    //type:message;payload:Hello;sender:123
    else if(separated.first() == "type:message") {
        QString message = QString();
        QString sender = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            message = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            sender = separated.first().remove("sender:");
        }
        if(message != QString() && sender != QString()) {
            message = sender + ": " + message;
            emit messageChatReceived(message);
        }
    }
    //type:readyLobby
    else if(separated.first() == "type:readyLobby") {
        emit readyLobbyReceived();
    }
    //type:updateClientReady;payload:111,222,333
    else if(separated.first() == "type:updateClientReady") {
        QStringList clientIdReadyList = QStringList();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            clientIdReadyList = separated.first().remove("payload:").split(QRegularExpression(","));
        }
        if(clientIdReadyList != QStringList()) {
            emit updateClientReady(clientIdReadyList);
        }
    }
    //type:readyScribble;payload:0x123456789;objectDraw:car
    else if(separated.first() == "type:readyScribble") {
        QString hexData = QString();
        QString objectDraw = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            hexData = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("objectDraw:")) {
            objectDraw = separated.first().remove("objectDraw:");
        }
        if(hexData != QString() && objectDraw != QString()) {
            emit readyScribbleReceived(objectDraw, hexData);
        }
    }
    //type:readyTakeaway;payload:111,222,333;images:0x111,0x222,0x333
    else if(separated.first() == "type:readyTakeaway") {
        QMap<QString, QString> clientImageMap = QMap<QString, QString>();
        QStringList userIdList = QStringList();
        QStringList imageList = QStringList();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            userIdList = separated.first().remove("payload:").split(QRegularExpression(","));
        }
        separated.pop_front();
        if(separated.first().contains("images:")) {
            imageList = separated.first().remove("images:").split(QRegularExpression(","));
        }

        if(userIdList.count() == imageList.count()) {
            for(int i = 0; i < userIdList.count(); i++) {
                clientImageMap[userIdList[i]] = imageList[i];
            }
            emit readyTakeawayReceived(clientImageMap);
        }
    }
    //type:readyGameOver;payload:123
    else if(separated.first() == "type:readyGameOver") {
        QString highestClientId = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            highestClientId = separated.first().remove("payload:");
        }

        if(highestClientId != QString()) {
            emit readyGameOverReceived(highestClientId);
        }
    }
}
