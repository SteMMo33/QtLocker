#ifndef IOBOARD_H
#define IOBOARD_H

#include <QtCore/QObject>
#include <QtWebSockets>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

#include "ambd002.h"



class IoBoard : public QObject
{
    Q_OBJECT
    // Q_PROPERTY(QString var READ getVar WRITE setVar NOTIFY varChanged)

public:

    typedef enum connectionType {
        CONNECTION_WS,              // Collegamento via websocket
        CONNECTION_SERIAL_GPU,      // Collegamento seriale con scheda GPUxx
        CONNECTION_SERIAL_AMDB002  // Collegamento seriale con scheda AMBD002
    } ConnectionType;

    enum {
        ACK =    0x06,
        DLE =    0x10,
        NAK =    0x15,
        ETB =    0x17,
        REP =    0x5A
    };


    enum IoRet {
        IORET_OK,
        IORET_ERR,
        IORET_UNSUPPORTED,
        IORET_PORTCLOSED,
    };
    Q_ENUMS(IoRet)


    IoBoard(QObject* parent = nullptr);
    virtual ~IoBoard();


    Q_INVOKABLE IoRet apriCassetto(int nCassetto);
    Q_INVOKABLE IoRet leggiCassetto(int nCassetto);
    Q_INVOKABLE IoRet setInternalTable(int nCassetti);


    IoRet setType(ConnectionType type, QString serialName);


private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onDestroyed();
    void onStateChanged(QAbstractSocket::SocketState state);

    void onTextMessageReceived(QString message);
    void onBinMessageReceived(QByteArray message);
    void onError(QAbstractSocket::SocketError error);

private:
    QWebSocket _ws;
    ConnectionType _type;

    QByteArray _response;
    int _waitTimeout = 5000;

    Ambd002 _ambd002;

    // Seriale GPU
    QString _serialName;
    QSerialPort _serial;
    unsigned char crc( unsigned char* buffer, int size);
    int sendSerial( unsigned char* buffer, int size);
};


#endif // IOBOARD_H
