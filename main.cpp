#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "settings.h"
#include "ioboard.h"


static Settings settings;
static IoBoard ioboard(NULL);



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    qDebug() << "Platform: " << app.platformName();

    // Prova accesso settings
    qDebug() << "Farmacia: " << settings["farmacia"];

    return app.exec();
}
