#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Controllers/gamemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GameManager gameManager;
    gameManager.connectToHost("ws://127.0.0.1:2048");
    QQmlContext* root = engine.rootContext();
    root->setContextProperty("GameManager", &gameManager);

    //qmlRegisterType<GameManager>("com.qt.gameManager", 1, 0, "GameManager");

    const QUrl url(u"qrc:/DoodleClient/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}


//"type:requestId;payload:0;sender:0"
