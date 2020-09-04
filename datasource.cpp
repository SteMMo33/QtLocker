/**
  Classe che gestisce le richieste dei dati
  La sorgente per ora è il DB ma potrebbe essere di diverso tipo
*/

#include "datasource.h"

DataSource::DataSource()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("kiosk");
    db.setUserName("root");
    db.setPassword("amtek");
    _open = db.open();
    qDebug() << "[DataSource] open: " << _open;

}


DataSource::~DataSource()
{
    if(_open){
        db.close();
        db.removeDatabase("QMYSQL");
    }
};




Cassetti* DataSource::getCassetti()
{
    return nullptr;
};


Prenotazioni* DataSource::getPrenotazioni()
{
    return nullptr;
};



/**
 * @brief DataSource::getSettings
 * Lettura dei Settings dalla tabella omonima
 * @return
 */
Settings* DataSource::getSettings()
{
    Settings* set = new Settings();

    QSqlQuery query("select * from settings;");
    // Loop su tutti i valori in tabella
    while (query.next()) {
        // qDebug()<< query.value("name") << " > " << query.value("value");

        // Pulisce la stringa da eventuali apici estremi
        QString strCleanValue = query.value("value").toString();
        if (strCleanValue.startsWith("'")) strCleanValue.remove(0,1);
        if (strCleanValue.endsWith("'")) strCleanValue.remove( strCleanValue.length()-1, 1);

        QString strKey = query.value("name").toString();
        set->insert( strKey, strCleanValue);
    }
    return set;
};
