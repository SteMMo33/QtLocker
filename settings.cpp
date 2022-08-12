
#include "settings.h"

/**
 * @brief MachineSettings::MachineSettings
 * Costruttore che carica il contenuto della tabella 'settings' in memoria
 */
MachineSettings::MachineSettings()
{
    qDebug() << "Costruttore Settings";

    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("kiosk");
    db.setUserName("root");
    db.setPassword("amtek");
    bool ok = db.open();
    qDebug() << "[Settings] open: " << ok;

    if (ok){
        QSqlQuery query("select * from settings;");
        // Loop su tutti i valori in tabella
        while (query.next()) {
            // qDebug()<< query.value("name") << " > " << query.value("value");

            // Pulisce la stringa da eventuali apici estremi
            QString strCleanValue = query.value("value").toString();
            if (strCleanValue.startsWith("'")) strCleanValue.remove(0,1);
            if (strCleanValue.endsWith("'")) strCleanValue.remove( strCleanValue.length()-1, 1);

            _settings.insert( query.value("name").toString(), strCleanValue);
        }
        db.close();
        db.removeDatabase("QMYSQL");
    }
    */
}


void MachineSettings::insert(QString &key, QString &value)
{
    _settings.insert( key, value);
}
