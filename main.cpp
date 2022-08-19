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
 *
 * Questa versione del programma presuppone la presenza del
 * servizio ws-server in background. La comunicazione
 * avviene tramite websocket.
 *
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
    qDebug() << "Farmacia: " << settings->get("farmacia");
    qDebug() << "Cassetti: " << settings->get("numCassetti");
    qDebug() << "email: " << settings->get("emailFarmacia");
    qDebug() << "serial: " << settings->get("serial_port");

    IoBoard ioboard;
    ioboard.setType(IoBoard::CONNECTION_SERIAL_AMDB002, settings->get("serial_port"));

    // Oggetti pubblicati verso QML
    // qmlRegisterType<Settings>("com.amtek.locker", 1, 0, "Settings");
    // qmlRegisterType<Prenotazioni>("com.amtek.locker", 1, 0, "Prenotazioni");
    // qmlRegisterType<IoBoard>("com.amtek.locker", 1, 0, "IoBoard"); Permette di istanziare da QML

    engine.rootContext()->setContextProperty( "ioBoard", &ioboard);
    engine.rootContext()->setContextProperty( "prenotazioni", prenotazioni);
    engine.rootContext()->setContextProperty( "mysettings", settings);
    engine.rootContext()->setContextProperty( "ds", &dataSource);

    engine.rootContext()->setContextProperty( "farmacia_name", settings->get("farmacia"));    // Per l'intestazione della finestra

    qmlRegisterType<Prenotazione>("com.amtek.locker", 1, 0, "Prenotazione");

    qRegisterMetaType<TipoPrenotazione>("TipoPrenotazione");
    qmlRegisterUncreatableType<TipoPrenotazioneClass>("com.amtek.locker", 1, 0, "TipoPrenotazione", "Not creatable as it is an enum type");

    engine.load(url);

    // Cassetti
    qDebug() << "Cassetti da DB: " << cassetti->length();
	
    return app.exec();
}

