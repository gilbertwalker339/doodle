#ifndef LOBBYHANDLER_H
#define LOBBYHANDLER_H

#include <QObject>
#include <QMap>
#include <random>
#include <QDebug>

class LobbyHandler : public QObject
{
    Q_OBJECT
public:
    explicit LobbyHandler(QObject *parent = nullptr);
    virtual ~LobbyHandler();
    void addClientId(QString clientId);
    void setLobbyId(QString id);
    QStringList clientIdList();
    void setClientIdReady(const QString& clientId, bool isReady);
    QStringList clientIdReadyList();
    bool isClientsInLobbyReady();
    void resetReadyLobby();
    QMap<QString, QString> clientImageMap();
    QString highestVote();
signals:
    void scribblesReady(const QString& objectDraw);
    void takeawayReady();
    void gameOverReady();

public slots:
    void drawnRequest(const QString& type, const QString& clientId, const QString& hexData);
    void voteRequest(const QString& clientId);

private:
    QString chooseObjectToDraw();

private:
    QString m_lobbyId;
    QMap<QString, bool> m_clientMap;
    QMap<QString, QString> m_clientImageMap;
    QMap<QString, int> m_voteMap;
};

#endif // LOBBYHANDLER_H
