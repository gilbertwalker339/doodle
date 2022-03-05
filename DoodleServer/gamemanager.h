#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QMap>
#include <QRandomGenerator>
#include "serversockethandler.h"
#include "messagehandler.h"
#include "lobbyhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);
    virtual ~GameManager();

signals:

private slots:
    void createGameRequest(const QString& clientId);
    void joinGameRequest(const QString& clientId, const QString& lobbyId);
    void messageRequest(const QString& clientId, const QString& lobbyId, const QString& message);
    void readyLobby(const QString& clientId, const QString& lobbyId);
    void scribblesReady(const QString& objectDraw);
    void takeawayReady();
    void gameOverReady();

private:
    ServerSocketHandler* m_server;
    MessageHandler* m_message;
    QMap<QString, LobbyHandler*> m_lobbyMap;
};

#endif // GAMEMANAGER_H
