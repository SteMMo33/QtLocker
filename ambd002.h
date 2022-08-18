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
        Err
    } AmbdRet;

    Ambd002();

    AmbdRet open(QString portName);
    AmbdRet close();

    AmbdRet setCoils();
    AmbdRet getCoils();


private:

    qint16 crc16(QByteArray &bytes);
    qint16 crc16(char* bytes, int len);


    QSerialPort _port;
};



#endif // AMBD002_H
