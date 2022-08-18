/**
  Classe che gestisce le richieste dei dati
  La sorgente per ora è il DB ma potrebbe essere di diverso tipo
*/

#include "datasource.h"

DataSource::DataSource()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("kiosk");
    db.setUserName("root");
    db.setPassword("amtek");
    _open = db.open();
    qDebug() << "[DataSource] open: " << _open;
}


DataSource::~DataSource()
{
    qDebug() << "[DataSource]D'tor";
    if(_open){
        qDebug() << "[DataSource] Close DB";
        db.close();
        db.removeDatabase("QMYSQL");
    }
};



/**
 * @brief DataSource::getCassetti
 * Lettura stato cassetti come in DB
 * @return
 */
Cassetti* DataSource::getCassetti()
{
    Cassetti* cassetti = new Cassetti();

    QSqlQuery query("select * from cassetti_detail;");
    while (query.next()) {
            Cassetto* cass = new Cassetto();
            cass->setVuoto(query.value("Vuoto").toBool());
            cassetti->append(*cass);
    }
    return cassetti;
};


Prenotazioni* DataSource::getPrenotazioni()
{
    Prenotazioni* prenotazioni = new Prenotazioni();
    return prenotazioni;
};



/**
 * @brief DataSource::getSettings
 * Lettura dei Settings dalla tabella omonima
 * @return
 */
MachineSettings* DataSource::getSettings()
{
    MachineSettings* set = new MachineSettings();

    QSqlQuery query("select * from settings;");

    if (query.isValid())
    {
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
    }
    else {
        set->insert( QString("serial_port"), QString("COM16"));
    }

    return set;
};




/**
 * @brief DataSource::checkCode
 * Verifica di un codice introdotto da UI
 * @param tipo
 * @param codice
 * @return
 */
Prenotazione* DataSource::checkCode(TipoPrenotazione tipo, QString codice)
{
    Prenotazione* p = nullptr;

    QString nameType = tipo == TipoPrenotazioneClass::TIPO_RITIRO ? "codice_prenotazione" : "numero_consegna";
    QString strQuery = QString("select * from prenotazioni where %1='%2';").arg(nameType).arg(codice);
    QSqlQuery query(strQuery);

    qDebug() << "[DataSource] query = '" << strQuery;
    qDebug() << "[DataSource] size = " << strQuery.size();
    qDebug() << "[DataSource] isEmpty = " << strQuery.isEmpty();

    if (query.next()) {
        p = new Prenotazione();

        p->_id = query.value("id").toUInt();
        p->_isDepositata = query.value("depositata").toBool();
        p->_isRitirata = query.value("ritirata").toBool();
        p->_cassetto = query.value("id_cassetto_ws").toUInt();
        p->_importo = query.value("importo_da_pagare").toFloat();

        qDebug()<< "[DataSource] p:" << p;
    }

    checkResultReady();     // Segnale !!

    return p;
};


