#include "prenotazioni.h"


Prenotazioni::Prenotazioni()
{
    qDebug() << "C'tor Prenotazioni";
}



/**
 * @brief Prenotazioni::CheckCode
 * @param tipo
 * @param code
 * @return
 */
int Prenotazioni::checkCode(TipoPrenotazione tipo, QString code)
{
    qDebug() << "[checkCode] Tipo: " << tipo << " - Code:" << code;
    // qDebug() << "[checkCode] Tipo: - Code:" << code;
    return 1;
}




int Prenotazioni::sendEmail()
{
    qDebug() << "[Prenotazioni] sendEmail";

    SendEmail* email = new SendEmail();
    email->send();

    return 1;
}
