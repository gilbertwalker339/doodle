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
    void registerId(const QString& id);
    void joinLobby(const QString& lobbyId, QStringList clientIdList);
    void failedLobby();
    void updateClientInLobby(const QStringList& clientIdList);
    void messageChatReceived(const QString& message);
    void readyLobbyReceived();
    void updateClientReady(const QStringList& clientIdReadyList);
    void readyScribbleReceived(const QString& objectDraw, const QString& hexData);
    void readyTakeawayReceived(QMap<QString, QString> clientImageMap);
    void readyGameOverReceived(QString highestClientId);

public slots:
    void textMessageReceived(const QString& message);
};

#endif // MESSAGEHANDLER_H
