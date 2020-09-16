#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "ioboard.h"
#include "datasource.h"
#include "printer.h"



/**
 * @brief main
 * @param argc
 * @param argv
 * Punto d'ingresso dell'applicazione
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qDebug() << "Platform: " << app.platformName();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    // Preparazione ambiente

    Printer printer;

    DataSource dataSource;
    Prenotazioni* prenotazioni = dataSource.getPrenotazioni();
    MachineSettings* settings = dataSource.getSettings();
    Cassetti* cassetti = dataSource.getCassetti();

    // Accesso 'settings'
    qDebug() << "Farmacia: " << settings->value("farmacia").toString();
    qDebug() << "Cassetti: " << settings->value("numColumn");
    qDebug() << "email: " << settings->value("emailFarmacia").toString();
    qDebug() << "serial: " << settings->value("serial_port").toString();

    IoBoard ioboard;
    ioboard.setType(IoBoard::CONNECTION_SERIAL, settings->value("serial_port").toString());

    // Oggetti pubblicati verso QML
    // qmlRegisterType<Settings>("com.amtek.locker", 1, 0, "Settings");
    // qmlRegisterType<Prenotazioni>("com.amtek.locker", 1, 0, "Prenotazioni");
    // qmlRegisterType<IoBoard>("com.amtek.locker", 1, 0, "IoBoard"); Permette di istanziare da QML

    engine.rootContext()->setContextProperty( "ioBoard", &ioboard);
    engine.rootContext()->setContextProperty( "prenotazioni", prenotazioni);
    engine.rootContext()->setContextProperty( "mysettings", settings);
    engine.rootContext()->setContextProperty( "ds", &dataSource);

    engine.rootContext()->setContextProperty( "farmacia_name", settings->value("farmacia").toString());    // Per l'intestazione della finestra

    qmlRegisterType<Prenotazione>("com.amtek.locker", 1, 0, "Prenotazione");

    qRegisterMetaType<TipoPrenotazione>("TipoPrenotazione");
    qmlRegisterUncreatableType<TipoPrenotazioneClass>("com.amtek.locker", 1, 0, "TipoPrenotazione", "Not creatable as it is an enum type");

    engine.load(url);

    // Cassetti
    qDebug() << "Cassetti da DB: " << cassetti->length();
	
    return app.exec();
}

