#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QByteArray>
#include "clientsockethandler.h"
#include "messagehandler.h"

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lobbyId READ lobbyId WRITE setLobbyId NOTIFY lobbyIdChanged)
    Q_PROPERTY(QStringList clientIdInLobby READ clientIdInLobby WRITE setClientIdInLobby NOTIFY clientIdInLobbyChanged)
    Q_PROPERTY(QString objectDraw READ objectDraw WRITE setObjectDraw NOTIFY objectDrawChanged)
    Q_PROPERTY(QString scribblePath READ scribblePath WRITE setScribblePath NOTIFY scribblePathChanged)
    Q_PROPERTY(QStringList imagePathList READ imagePathList WRITE setImagePathList NOTIFY imagePathListChanged)
    Q_PROPERTY(QString bestClientId READ bestClientId WRITE setBestClientId NOTIFY bestClientIdChanged)
public:
    explicit GameManager(QObject *parent = nullptr);
    virtual ~GameManager();

    void connectToHost(const QString& url);

    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE void joinGameRequest(QString lobbyId);
    Q_INVOKABLE void sendMessageRequest(QString message);
    Q_INVOKABLE void readyRequest();
    Q_INVOKABLE void drawnRequest();
    Q_INVOKABLE void voteRequest(QString imagePath);
    Q_INVOKABLE QString bestImagePath();
signals:
    void createGameFinished();
    void failedLobby();
    void messageChatReceived(const QString& message);
    void readyLobbyReceived();
    void updateClientReady(const QStringList& clientIdReadyList);
    void nextToTakeway();
    void nextToVote();
    void readyGameOverReceived(QString highestClientId);

    void lobbyIdChanged();
    void clientIdInLobbyChanged();
    void objectDrawChanged();
    void scribblePathChanged();
    void imagePathListChanged();
    void bestClientIdChanged();
private slots:
    void registerId(QString id);
    void joinLobby(QString id, QStringList clientIdList);
    void readyScribbleReceived(const QString& objectDraw, const QString &hexData);
    void readyTakeawayReceived(QMap<QString, QString> clientImageMap);

    QString lobbyId() const;
    void setLobbyId(QString lobbyId);
    QStringList clientIdInLobby() const;
    void setClientIdInLobby(QStringList clientIdList);
    QString objectDraw();
    void setObjectDraw(QString objectDraw);
    QString scribblePath();
    void setScribblePath(QString path);
    QStringList imagePathList();
    void setImagePathList(QStringList imagePathList);
    QString bestClientId();
    void setBestClientId(QString clientId);
private:
    QString m_lobbyId;
    QString m_clientId;
    QString m_objectDraw;
    QString m_scribblePath;
    QString m_highestClientId;
    QStringList m_imagePathList;
    QStringList m_clientIdInLobby;
    QStringList m__clientIdReady;
    ClientSocketHandler* m_client;
    MessageHandler* m_message;
};

#endif // GAMEMANAGER_H
