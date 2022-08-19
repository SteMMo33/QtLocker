#include "cassetti.h"


/**
 * @brief Cassetti::Cassetti
 * Costruttore
 */
Cassetti::Cassetti()
{
    qDebug() << "C'tor Cassetti";

    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("kiosk");
    db.setUserName("root");
    db.setPassword("amtek");
    bool ok = db.open();
    qDebug() << "[Cassetti] open: " << ok;

    if (ok){
        QSqlQuery query("select * from cassetti_detail;");
        while (query.next()) {
            Cassetto* cass = new Cassetto();
            cass->isEmpty = query.value("Vuoto").toBool();
            _cassetti.append(*cass);

            ++_number;
        }
        db.close();
        db.removeDatabase("MYSQL");
    }
    */
}
