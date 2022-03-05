#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include <QRegularExpression>

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageHandler(QObject *parent = nullptr);
    virtual ~MessageHandler();

signals:
    void createGameRequest(const QString& clientId);
    void joinGameRequest(const QString& clientId, const QString& lobbyId);
    void messageRequest(const QString& clientId, const QString& lobbyId, const QString& message);
    void readyLobby(const QString& clientId, const QString& lobbyId);
    void drawnRequest(const QString& typeData, const QString& clientId, const QString& hexData);
    void voteRequest(const QString& clientId);

public slots:
    void textMessageReceived(const QString& message);

};

#endif // MESSAGEHANDLER_H
