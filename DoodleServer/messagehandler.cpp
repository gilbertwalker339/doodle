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
    //type:createGame;payload:0;sender:123
    //type:joinGame;payload:9932;sender:123
    //type:message;payload:9932;message:Hello;sender:123
    //type:readyLobby;payload:9932;sender:123
    //type:scribbleData;payload:0x123456789;sender:123
    //type:vote;payload:123;sender:111
    qDebug() << message;
    QStringList separated = message.split(QRegularExpression(";"));

    if(separated.first() == "type:createGame") {
        QString clientId = QString();
        separated.pop_front();
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            clientId = separated.first().remove("sender:");
        }

        if(clientId != QString()) {
            emit createGameRequest(clientId);
        }
    }
    //type:joinGame;payload:9932;sender:123
    else if(separated.first() == "type:joinGame") {
        QString clientId = QString();
        QString lobbyId = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            lobbyId = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            clientId = separated.first().remove("sender:");
        }

        if(clientId != QString() && lobbyId != QString()) {
            emit joinGameRequest(clientId, lobbyId);
        }
    }
    //type:message;payload:9932;message:Hello;sender:123
    else if(separated.first() == "type:message") {
        QString clientId = QString();
        QString lobbyId = QString();
        QString message = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            lobbyId = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("message:")) {
            message = separated.first().remove("message:");
        }
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            clientId = separated.first().remove("sender:");
        }
        if(clientId != QString() && lobbyId != QString() && message != QString()) {
            emit messageRequest(clientId, lobbyId, message);
        }
    }
    //type:readyLobby;payload:9932;sender:123
    else if(separated.first() == "type:readyLobby") {
        QString clientId = QString();
        QString lobbyId = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            lobbyId = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            clientId = separated.first().remove("sender:");
        }

        if(clientId != QString() && lobbyId != QString()) {
            emit readyLobby(clientId, lobbyId);
        }
    }
    //type:scribbleData;payload:0x123456789;sender:123
    else if(separated.first() == "type:scribbleData" || separated.first() == "type:takeawayData") {
        QString payload = QString();
        QString sender = QString();
        QString typeData = separated.first().remove("type:");
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            payload = separated.first().remove("payload:");
        }
        separated.pop_front();
        if(separated.first().contains("sender:")) {
            sender = separated.first().remove("sender:");
        }

        if(payload != QString() && sender != QString() && typeData != QString()) {
            emit drawnRequest(typeData, sender, payload);
        }
    }
    //type:vote;payload:123;sender:111
    else if(separated.first() == "type:vote") {
        QString clientId = QString();
        separated.pop_front();
        if(separated.first().contains("payload:")) {
            clientId = separated.first().remove("payload:");
        }
        if(clientId != QString()) {
            emit voteRequest(clientId);
        }
    }
}
