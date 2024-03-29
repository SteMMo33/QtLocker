/*!
    @author SM

    @abstract
  Protocollo per la porta seriale Protocollo PC - scheda CPU Locker 80 vers. 1.00.doc

  Viene inserita la possibilità di selezionare la modalità di comunicazione:
  - seriale con scheda GPU
  - serial con scheda AMBD002
  - websocket

!*/

#include "ioboard.h"




/**
 * @brief IoBoard::IoBoard
 * Costruttore oggetto IoBoard che comunica via websocket
 */
//! [constructor]
IoBoard::IoBoard(QObject* parent) : QObject(parent), _type(CONNECTION_SERIAL_GPU), _ambd002()
{
    qDebug() << "C'tor IoBoard type:" << _type << this;

    if (_type == CONNECTION_WS)
    {
        // -- Collegamento con websocket

        QObject::connect( &_ws, &QWebSocket::connected, this, &IoBoard::onConnected);
        QObject::connect( &_ws, &QWebSocket::disconnected, this, &IoBoard::onDisconnected);
        QObject::connect( &_ws, &QWebSocket::destroyed, this, &IoBoard::onDestroyed);
        QObject::connect( &_ws, &QWebSocket::stateChanged, this, &IoBoard::onStateChanged);

        connect( &_ws, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            [=](QAbstractSocket::SocketError error){
                qDebug() << "[IoBoard] Errore: " << error;
            }
        );

        QUrl url ("ws://localhost:7681");
        // url.setHost("10.191.40.216");

        qDebug() << "[IoBoard] url: " << url.toString() << " - Scheme: " << url.scheme() << " - Host: " << url.host() << " - Port: " << url.port();
        qDebug() << "[IoBoard] state:" << _ws.state();
        _ws.open(url);
        qDebug() << "[IoBoard] state:" << _ws.state();

    }
    else if (_type == CONNECTION_SERIAL_GPU)  // Versione SERIAL_GPU
    {
        // -- Collegamento con la porta seriale
        const auto infos = QSerialPortInfo::availablePorts();
        qDebug() << "Lista porte seriali:";
        for (const QSerialPortInfo &info : infos)
            qDebug() << info.portName();
        qDebug() << "--- Fine lista ";

    } // if SERIAL
}
//! [constructor]




IoBoard::~IoBoard()
{
    qDebug() << "[IoBoard] D'ctor" << this;

    if (_type == CONNECTION_WS)
        _ws.close();
    else if (_type == CONNECTION_SERIAL_AMDB002)
        _ambd002.close();
    else
        _serial.close();
};



/**
 * @brief IoBoard::onConnected
 * @note Versione CONNECTION_WS
 */
//! [onConnected]
void IoBoard::onConnected()
{
    qDebug() << "[IoBoard] WebSocket connected";

    QObject::connect( &_ws, &QWebSocket::textMessageReceived, this, &IoBoard::onTextMessageReceived);
    QObject::connect( &_ws, &QWebSocket::binaryMessageReceived, this, &IoBoard::onBinMessageReceived);

    // _ws.sendTextMessage(QStringLiteral("{ \"LetturaCassetto\": 1}"));
    _ws.sendTextMessage(QStringLiteral("startKiosk"));
}
//! [onConnected]


/**
 * @brief IoBoard::onDisconnected
 */
void IoBoard::onDisconnected()
{
    qDebug() << "[IoBoard] WebSocket disconnected";
}


/**
 * @brief IoBoard::onTextMessageReceived
 * Gestore delle risposte tipo TESTO dalla scheda IO
 * @param message
 */
void IoBoard::onTextMessageReceived(QString message)
 {
    qDebug() << "[IoBoard] Message received:" << message;
 }



/**
 * @brief IoBoard::onBinMessageReceived
 * Gestore delle risposte tipo BINARIO dalla scheda IO
 * @param message
 */
void IoBoard::onBinMessageReceived(QByteArray message)
{
    qDebug() << "[IoBoard] Binary message: " << message;
};


/**
 * @brief IoBoard::onError
 * @param error
 */
void IoBoard::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "[IoBoard] Error: " << error;
};


/**
 * @brief IoBoard::onDestroyed
 */
void IoBoard::onDestroyed()
{
    qDebug() << "[IoBoard] Destroyed";
};


void IoBoard::onStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "[IoBoard] StateChanged:" << state;
};



/**
 * @brief IoBoard::setType
 * @param type
 * @param serialName
 * @return
 */
IoBoard::IoRet IoBoard::setType(ConnectionType type, QString serialName)
{
    _type = type;
    _serialName = serialName;


    qDebug() << "[IoBoard] Serial:" << _serialName;

    if (_type == CONNECTION_SERIAL_GPU)
    {
        if (_serial.isOpen()) _serial.close();

        _serial.setPortName(_serialName);
        if (!_serial.open(QIODevice::ReadWrite)) {
            qDebug() << tr("!! Can't open %1, error code %2").arg(_serialName).arg(_serial.error());
            return IORET_ERR;
        }
        // Impostazione porta
        _serial.setBaudRate(9600);
        _serial.setDataBits(QSerialPort::Data8);
        _serial.setFlowControl(QSerialPort::NoFlowControl);
        _serial.setParity(QSerialPort::NoParity);
        _serial.setStopBits(QSerialPort::OneStop);
        return IORET_OK;
    }
    else if (_type == CONNECTION_SERIAL_AMDB002)
    {
        // Apertura della comunicazione
        Ambd002::AmbdRet ret = _ambd002.open(serialName);
        if (ret != Ambd002::Ok)
            return IORET_ERR;

        // Configurazione dell'impianto
        _ambd002.configCoil( 1, 1, Ambd002::LOCK_A);
        _ambd002.configCoil( 2, 1, Ambd002::LOCK_B);
        _ambd002.configCoil( 3, 1, Ambd002::FAN_A1);
        _ambd002.configCoil( 4, 1, Ambd002::FAN_A2);
        _ambd002.configCoil(22, 2, Ambd002::LOCK_A);
    }
    return IORET_UNSUPPORTED;
}



/**
 * @brief IoBoard::crc
 * Calcolo del CRC versione per GPU
 * @param buffer
 * @param size
 * @return
 */
unsigned char IoBoard::crc( unsigned char* buffer, int size)
{
    unsigned char crc = 0x7F;
    int i = 0;
    while(i<size)   crc ^= buffer[i++];
    return crc;
}



/// Funzione per la gestione dell'apertura e chiusura cassetto
/// \brief IoBoard::gestisciCassetto
/// \param nCassetto
/// \return
///
IoBoard::IoRet IoBoard::gestisciCassetto(int nCassetto)
{
    qDebug() << "[IoBoard] gestisciCassetto:" << nCassetto;

    IoRet ret = apriCassetto(nCassetto);
    ret = leggiCassetto(nCassetto);

    return IoBoard::IORET_OK;
};



/**
 * @brief IoBoard::apriCassetto
 * @param nCassetto
 * @return
 */
IoBoard::IoRet IoBoard::apriCassetto(int nCassetto)
{
    qDebug() << "[IoBoard] apriCassetto:" << nCassetto;

    if (_type==CONNECTION_WS){
        _ws.sendTextMessage(QString("{\"AperCassetto\":%1}").arg(nCassetto));
    }
    else if (_type==CONNECTION_SERIAL_AMDB002)
    {
        // Genera un impulso ampio 2 secondi sul pin
        qDebug() << "[AMBD002] apriCassetto " << nCassetto;

        Ambd002::AmbdRet ret = _ambd002.setOutput( nCassetto, 1);
        qDebug() << "[Ioboard] ret " << ret;
        if (ret == Ambd002::Ok){
            QThread::sleep(2);
            ret = _ambd002.setOutput( nCassetto, 0);
            qDebug() << "[Ioboard] ret " << ret;
        }
    }
    else  // CONNECTION_GPU
    {
        if (!_serial.isOpen()){
            return IORET_PORTCLOSED;
        }
        unsigned char cmd[] = { 0x3B, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF };
        cmd[5] = char(nCassetto);
        cmd[6] = crc( cmd, 6);
        int ret = sendSerial(cmd, 7);
        if (ret){
            if (_response.at(0)==ACK)
                qDebug() << "[] Apertura OK";
        }
    }
    return IORET_OK;
};



/**
 * @brief IoBoard::leggiCassetto
 * Lettura output digi
 * @param nCassetto
 * @return
 */
IoBoard::IoRet IoBoard::leggiCassetto(int nCassetto)
{
    qDebug() << "[IoBoard] leggiCassetto:" << nCassetto;

    if (_type==CONNECTION_WS)
    {
        _ws.sendTextMessage(QString("{\"LeggiCassetto\":%1}").arg(nCassetto));
    }
    else if (_type == CONNECTION_SERIAL_AMDB002)
    {
        bool bStato;
        Ambd002::AmbdRet ret = _ambd002.getInput( 1, Ambd002::LOCK_A_STS1, &bStato);
        qDebug() << "[IoBoard][leggiCassetto] ret:" << ret << " - Stato:" << bStato;
        if (ret==Ambd002::Ok)
            return bStato ? IORET_HI : IORET_LO;
        else
            return IORET_ERR;
    }
    else if (_type == CONNECTION_SERIAL_GPU)
    {
        unsigned char cmd[] = { 0x3C, 0x01, 0xFF, 0xFF };
        cmd[2] = (char)nCassetto;
        cmd[3] = crc( cmd, 3);
        int ret = sendSerial(cmd, 4);
        if (ret > 0){
            if (_response.at(1)==0x3C)
            {   // Controlla che sia una sua risposta
                // Decodifica risposta
                qDebug() << "[] index:" << QChar(_response.at(3)) << " - " << (_response.at(4) ? "aperto" : "chiuso");
            }
        }
        else {
            qDebug() << "[IoBoard] Errore comando: " << ret;
        }
    }
    else return IORET_UNSUPPORTED;
    return IORET_OK;
};



/**
 * @brief IoBoard::sendSerial
 * @param buffer
 * @param size
 * @return
 */
int IoBoard::sendSerial(unsigned char* buffer, int size)
{
    int waitTimeout = 5000;

    qDebug() << "[IoBoard][sendSerial] TX:" << QByteArray((char*)buffer, size).toHex() << this;
    _serial.write((char*)buffer, size);

    if (_serial.waitForBytesWritten(waitTimeout)) {
        // qDebug() << "[] Sent.." << this;
        // read response
        if (_serial.waitForReadyRead(waitTimeout*3)) {
            _response = _serial.readAll();
            while (_serial.waitForReadyRead(10))
                _response += _serial.readAll();
            qDebug() << "[] Read:" << _response.toHex();
        }
        else {
            qDebug() << "[] TO Read";
            return -1;
        }
    }
    else {
        qDebug() << "[sendSerial] TO Write";
        return -2;
    }
    //
    // Controllo risposta
    if (_response.at(0)==REP)
        return _response.length();
    else if (_response.at(0)==DLE){
        qDebug() << "[] DLE";
    }
    else if (_response.at(0)==ETB){
        qDebug() << "[] ETB";
    }
    return -4;
}



/**
 * @brief IoBoard::setInternalTable
 * Funzione per settare la tabella interna alla CPU per associazione codice - cassetto
 * ed abilitare tutti i cassetti
 * @note Solo per seriale GPU
 */
IoBoard::IoRet IoBoard::setInternalTable(int nCassetti)
{
    if (_type != CONNECTION_SERIAL_GPU)
        return IORET_UNSUPPORTED;

    int c = 1;
    while (c <= nCassetti){
        unsigned char cmd[] = { 0x04, 0x08, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xEE };
        cmd[5] = c;
        cmd[9] = c;
        cmd[10] = crc( cmd, 10);
        int ret = sendSerial(cmd, 11);
        if (ret){
            if (_response.at(0)==ACK)
                qDebug() << "[] enable " << QString(c) << " OK";
            else
                qDebug() << "[] enable " << QString(c) << " ERR " << ret;
        }
        ++c;
    }
    return IORET_OK;
}

