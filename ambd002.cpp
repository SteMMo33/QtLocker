
#include "ambd002.h"
#include "QThread"


Ambd002::Ambd002()
{};



/**
 * Impostazione ed apertura della porta di comunicazione
 * @brief Ambd002::open
 * @param portName Nome della porta seriale
 * @return
 */
Ambd002::AmbdRet Ambd002::open(QString portName)
{
    qDebug() << "[Ambd002][open] " << portName;

    _port.setPortName(portName);
    _port.setBaudRate(QSerialPort::Baud38400);
    _port.setStopBits(QSerialPort::OneStop);
    _port.setDataBits(QSerialPort::Data8);
    _port.setParity(QSerialPort::NoParity);
    _port.setFlowControl(QSerialPort::NoFlowControl);

    bool ret = _port.open(QIODevice::ReadWrite);
    qDebug() << "[Ambd002][open] open " << ret;
    return ret ? Ambd002::Ok : AmbdRet::Err;
}



Ambd002::AmbdRet Ambd002::close()
{
    _port.close();
    return Ambd002::Ok;
}


void dump(QByteArray& ba)
{
    QDebug dbg = qDebug().nospace().noquote();
    for(uchar b : ba)
    {
        dbg << QString("%1").arg( (uint)b, 2, 16, QChar('0')) << " ";
    }}


void dump(char* buffer, int size)
{
    QByteArray ba = QByteArray(buffer, size);
    dump(ba);
}



/**
 * Lettura del registro COILS
 * @brief getCoils
 * @param nAddr
 * @return
 */
Ambd002::AmbdRet Ambd002::getCoils(uchar nAddr, uint16_t* pValue)
{
    qDebug() << "[ambd002][getCoils] addr: " << nAddr;

    if (!_port.isOpen())
        return Ambd002::Err;

    char bBufferTmp[] = { 0x01, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00 }; //Send read coils request
    int len = sizeof(bBufferTmp);

    bBufferTmp[0] = nAddr; //Set address
    quint16 crc_16 = crc16( bBufferTmp, len-2);

    bBufferTmp[6] = (uchar)(crc_16 & 0xFF);
    bBufferTmp[7] = (uchar)(crc_16 >> 8);

    QByteArray reply = sendAndReceive( bBufferTmp, len);
    if (reply.length()==0)
        return AmbdRet::Timeout;

    dump (reply);

    uint16_t coils = (uint16_t)((reply[4] << 8) + reply[3]);
    qDebug() << "Coils: " << coils << QString("%1").arg( coils, 2, 16, QChar('0'));
    if (pValue) *pValue = coils;
    return Ambd002::Ok;
}


/**
 * Lettura del registro DISCRETE INPUT
 * @brief getDicreteInput
 * @param nAddr
 * @param pValue Puntatore che riceve il valore letto
 * @return
 */
Ambd002::AmbdRet Ambd002::getDicreteInput(uchar nAddr, uint16_t* pValue)
{
    qDebug() << "[ambd002][getDicreteInput] addr: " << nAddr;

    if (!_port.isOpen())
        return Ambd002::Err;

    char bBufferTmp[] = { 0x01, 0x02, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00 }; //Send request
    int len = sizeof(bBufferTmp);

    bBufferTmp[0] = nAddr; //Set address
    quint16 crc_16 = crc16( bBufferTmp, len-2);

    bBufferTmp[6] = (uchar)(crc_16 & 0xFF);
    bBufferTmp[7] = (uchar)(crc_16 >> 8);

    QByteArray reply = sendAndReceive( bBufferTmp, len);
    if (reply.length()==0)
        return AmbdRet::Timeout;

    uint16_t inputs = (uint16_t)(reply[4] << 8);
    inputs += (uchar)(reply[3]);
    qDebug() << "Inputs: " << inputs << QString("%1").arg( inputs, 4, 16, QChar('0'));
    if (pValue) *pValue = inputs;
    return Ambd002::Ok;
}


/**
 * @brief Ambd002::configCoil
 * Configura il sistema associando un indice ad una scheda e pin
 * @param nIndex
 * @param nAddr
 * @param coil
 * @return
 */
Ambd002::AmbdRet Ambd002::configCoil( int nIndex, int nAddr, Ambd002::Coil coil)
{
    Board board = { nAddr, coil };
    _systemMap.insert( nIndex, board);
    return Ok;
};



/**
 * @brief Ambd002::setOutput
 * Imposta nello stato indicato l'output nIndex
 * @param nIndex Indice della board
 * @param bState Stato
 * @return
 */
Ambd002::AmbdRet Ambd002::setOutput( int nIndex, bool bState)
{
    if (!_systemMap.contains(nIndex))
        return AmbdRet::Err;

    Board board = _systemMap[nIndex];

    uint16_t coils;
    AmbdRet ret = getCoils( board.nAddr, &coils);

    if (bState){
        coils ^= 1 << board.coil;
    }
    else {
        coils &= ~(1 << board.coil);
    }
    ret = setCoils( board.nAddr, coils);
    return ret;
};



Ambd002::AmbdRet Ambd002::getOutput( int nIndex, bool* pbState)
{
    if (pbState==NULL)
        return AmbdRet::Err;

    if (!_systemMap.contains(nIndex))
        return Err;

    Board board = _systemMap[nIndex];

    uint16_t coils;
    AmbdRet ret = getCoils( board.nAddr, &coils);
    if (ret == Ok){
        *pbState = coils & (1 << board.coil);
        return Ok;
    }
    return ret;
};



/**
 * @brief Ambd002::getInput
 * Lettura di un input discreto
 * @param nIndex
 * @param pbState
 * @return
 */
Ambd002::AmbdRet Ambd002::getInput( int nIndex, Ambd002::Input pin, bool* pbState)
{
    if (pbState==NULL)
        return AmbdRet::Err;

    if (!_systemMap.contains(nIndex))
        return Err;

    Board board = _systemMap[nIndex];

    uint16_t input;
    AmbdRet ret = getDicreteInput( board.nAddr, &input);
    if (ret == Ok){
        *pbState = input & (1 << pin);
        return Ok;
    }
    return ret;
};


/**
 * Scrittura del registro COILS
 * @brief setCoils
 * @param nAddr
 * @return
 */
Ambd002::AmbdRet Ambd002::setCoils(uchar nAddr, uint16_t nCoils)
{
    qDebug() << "[ambd002][setCoils] addr: " << nAddr << "- coil:" << nCoils;

    if (!_port.isOpen())
        return Ambd002::Err;

    char bBufferTmp[] = { 0x01, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x02, 0x00, 0x00, 0x00, 0x00 }; //Send request
    int len = sizeof(bBufferTmp);

    bBufferTmp[0] = nAddr; //Set address
    bBufferTmp[7] = (nCoils >> 8);
    bBufferTmp[8] = (nCoils & 0xFF);

    quint16 crc_16 = crc16( bBufferTmp, len-2);
    bBufferTmp[9] = (uchar)(crc_16 & 0xFF);
    bBufferTmp[10] = (uchar)(crc_16 >> 8);

    QByteArray reply = sendAndReceive( bBufferTmp, len);
    if (reply.length()==0)
        return AmbdRet::Timeout;
    return Ambd002::Ok;
}



/**
 * Lettura del registro VERSIONE FIRMWARE
 * @brief getFirmware
 * @param
 * @return
 */
Ambd002::AmbdRet Ambd002::getFirmware(uchar nAddr)
{
    qDebug() << "[ambd002][getFirmware] addr: " << nAddr;

    if (!_port.isOpen())
        return Ambd002::Err;

    char bBufferTmp[] = { 0x01, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00 }; //Send read coils request
    int len = sizeof(bBufferTmp);

    bBufferTmp[0] = nAddr; //Set address
    quint16 crc_16 = crc16( bBufferTmp, len-2);

    bBufferTmp[6] = (uchar)(crc_16 & 0xFF);
    bBufferTmp[7] = (uchar)(crc_16 >> 8);

    QByteArray reply = sendAndReceive( bBufferTmp, len);
    if (reply.length()==0)
        return AmbdRet::Timeout;

    dump (reply);

    uint16_t fwHi = (reply[3] >> 4)*10 + (reply[3] & 0x0F);
    uint16_t fwLo = (reply[4] >> 4)*10 + (reply[4] & 0x0F);
    uint16_t model = (reply[5] << 8) + reply[6];

    qDebug().nospace() << "Fw: " << fwHi << "." << fwLo << " - Model: " << model;
    return AmbdRet::Ok;
}



/**
 * Lettura del registro TEMPERATURE
 * Ritorna le temperature rilevate dalle due sonde di ogni scheda
 * @brief getTemperatures
 * @param nAddr Indirizzo scheda
 * @return
 */
Ambd002::AmbdRet Ambd002::getTemperatures(uchar nAddr)
{
    qDebug() << "[ambd002][getTemperatures] addr: " << nAddr;

    if (!_port.isOpen())
        return Ambd002::Err;

    char bBuffer[] = { 0x01, 0x04, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00 };
    int len = sizeof(bBuffer);

    bBuffer[0] = nAddr; //Set address
    quint16 crc_16 = crc16( bBuffer, len-2);

    bBuffer[6] = (uchar)(crc_16 & 0xFF);
    bBuffer[7] = (uchar)(crc_16 >> 8);

    QByteArray reply = sendAndReceive( bBuffer, len);
    if (reply.length()==0)
        return AmbdRet::Timeout;

    uint16_t tempa = (reply[3] << 8) + reply[4];
    uint16_t tempb = (reply[5] << 8) + reply[6];
    qDebug().nospace() << "TempA: " << tempa << " - TempB: " << tempb;

    return AmbdRet::Ok;
}




/**
  * Calcolo del CRC di tipo MODBUS RTU
  *
*/
quint16 Ambd002::crc16(char* bytes, int len)
//qint16 Ambd002::crc16(QByteArray &bytes)
{
    quint16 crc = 0xFFFF;

    for (int pos = 0; pos < len; pos++)
    {
        crc ^= (qint16)bytes[pos];          // XOR byte into least sig. byte of crc
        for (int i = 8; i != 0; i--)
        {    // Loop over each bit
                 if ((crc & 0x0001) != 0)
                 {      // If the LSB is set
                     crc >>= 1;                    // Shift right and XOR 0xA001
                     crc ^= 0xA001;
                 }
                 else                            // Else LSB is not set
                     crc >>= 1;                    // Just shift right
        }
    }
    // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
    return crc;
}



QByteArray Ambd002::sendAndReceive(char* data, int len)
{
    dump( data, len);

    _port.write( data, len);
    _port.waitForBytesWritten(500);

    _port.waitForReadyRead(500);

    QByteArray reply = _port.readAll();
    dump(reply);
    return reply;
}

