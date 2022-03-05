#ifndef CLIENTSOCKETHANDLER_H
#define CLIENTSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>

class ClientSocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocketHandler(QObject *parent = nullptr);
    virtual ~ClientSocketHandler();

    void connectToHost(const QString& url);
    void sendTextMessageToServer(const QString& message);
signals:
    void textMessageFollowing(const QString& message);

private slots:
    void connected();
    void disconnected();
    void textMessageReceived(const QString& message);

private:
    QWebSocket* m_client;
};

#endif // CLIENTSOCKETHANDLER_H
