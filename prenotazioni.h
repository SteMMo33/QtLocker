#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <QObject>
#include <QDebug>

#include "sendemail.h"




class Prenotazione : public QObject
{
    Q_OBJECT

    // Variabili visibili al QML
    Q_PROPERTY(int cassetto MEMBER _cassetto)
    Q_PROPERTY(float importo MEMBER _importo)
    Q_PROPERTY(int id MEMBER _id)
    Q_PROPERTY(bool isDepositata MEMBER _isDepositata)
    Q_PROPERTY(bool isRitirata MEMBER _isRitirata)
    Q_PROPERTY(bool isScaduta MEMBER _isScaduta)

public:
    int _id;
    bool _isDepositata;
    bool _isRitirata;
    bool _isScaduta;
    float _importo;
    int _cassetto;


    friend QDebug operator<<(QDebug dbg, Prenotazione* prenotazione){
        qDebug() << "Prenotazione:";
        qDebug() << "! id: " << prenotazione->_id;
        qDebug() << "! cassetto: " << prenotazione->_cassetto;
        qDebug() << "! importo: " << prenotazione->_importo;
        qDebug() << "! depositata: " << prenotazione->_isDepositata;
        qDebug() << "! ritirata: " << prenotazione->_isRitirata;
        return dbg;
    };


private:
    //
};



/**
 * @brief The TipoPrenotazioneClass class
 * Classe che racchiude un enum
 */
class TipoPrenotazioneClass: public QObject
{
    Q_GADGET
private:
    explicit TipoPrenotazioneClass();
public:
    enum Value {
        TIPO_DEPOSITO,
        TIPO_RITIRO
    };
    Q_ENUM(Value)
};

typedef TipoPrenotazioneClass::Value    TipoPrenotazione;



/**
 * @brief The Prenotazioni class
 */
class Prenotazioni : public QObject
{
    Q_OBJECT

public:
    Prenotazioni();

    Q_INVOKABLE int checkCode(TipoPrenotazione tipo, QString code);
    Q_INVOKABLE int sendEmail();

private:
    // DataSource* ds;
};

#endif // PRENOTAZIONI_H
