#ifndef AMBD002_H
#define AMBD002_H

#include "QDebug"
#include "QString"
#include "QSerialPort"


class Ambd002 : public QObject {

    Q_OBJECT

public:

    // Codici di ritorno
    typedef enum {
        Ok,
        Err,
        Timeout
    } AmbdRet;

    // Valori per indicate la porta COIL
    typedef enum {
        LOCK_A,
        LOCK_B,
        FAN_A1,
        FAN_A2,
        FAN_B1,
        FAN_B2,
        OUT1,
        OUT2,
        UART2
    } Coil;

    // Valori per indicate la porta DISCERTE INPUT
    typedef enum {
        LOCK_A_STS1,
        LOCK_A_STS2,
        LOCK_A_STS3,
        LOCK_B_STS1,
        LOCK_B_STS2,
        LOCK_B_STS3,
        IN1,
        IN2,
    } Input;

    Ambd002();

    AmbdRet open(QString portName);
    AmbdRet close();

    AmbdRet configCoil( int nIndex, int nAddr, Coil coil);

    // Relativi a COILS
    AmbdRet setOutput( int nIndex, bool bState);
    AmbdRet getOutput( int nIndex, bool* pbState);
    AmbdRet getInput( int nIndex, Input pin, bool* pbState);

    // Richieste a basso livello
    AmbdRet setCoils(uchar nAddr, uint16_t value);
    AmbdRet getCoils(uchar nAddr, uint16_t* pValue);
    AmbdRet getFirmware(uchar nAddr);
    AmbdRet getTemperatures(uchar nAddr);
    AmbdRet getDicreteInput(uchar nAddr, uint16_t* pValue);


private:

    quint16 crc16(QByteArray &bytes);
    quint16 crc16(char* bytes, int len);
    QByteArray sendAndReceive(char* data, int len);

    struct Board {
        int nAddr;  // Indirizzo ModBus della scheda
        Coil coil;
    };

    QSerialPort _port;
    QMap<int, Board> _systemMap;   // Configurazione del sistema
    // uint16_t _coils;
};



#endif // AMBD002_H
