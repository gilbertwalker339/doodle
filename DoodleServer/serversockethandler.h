#ifndef SERVERSOCKETHANDLER_H
#define SERVERSOCKETHANDLER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>
#include <QMap>
#include <QRandomGenerator>

class ServerSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit ServerSocketHandler(QObject *parent = nullptr);
    virtual ~ServerSocketHandler();

    void sendTextMessageToClient(const QString& clientId, const QString& message);
    void sendTextMessageToClientList(const QStringList& clientIdList, const QString& message);
signals:
    void textMessageFollowing(const QString& message);

private slots:
    void newConnection();
    void textMessageReceived(const QString& message);
    void disconnected();

private:
    QWebSocketServer* m_server;
    QMap<QString, QWebSocket*> m_clientMap;
};

#endif // SERVERSOCKETHANDLER_H
