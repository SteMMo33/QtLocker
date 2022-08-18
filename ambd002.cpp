
#include "ambd002.h"


Ambd002::Ambd002()
{};


Ambd002::AmbdRet Ambd002::open(QString portName)
{
    qDebug() << "[Ambd002][open] " << portName;
    _port.setPortName(portName);
    bool ret = _port.open(QIODevice::ReadWrite);
    return ret ? Ambd002::Ok : AmbdRet::Err;
}



Ambd002::AmbdRet Ambd002::close()
{
    _port.close();
    return Ambd002::Ok;
}


/**
 * Lettura del registro COILS
 * @brief getCoils
 * @return
 */
Ambd002::AmbdRet Ambd002::getCoils()
{
    if (!_port.isOpen())
        return Ambd002::Err;

    //int iReaderr = 0;
    char bBufferTmp[] = { 0x01, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00 }; //Send read coils request
    int len = sizeof(bBufferTmp);

    bBufferTmp[0] = 0; //Set address
    qint16 crc_16 = crc16( bBufferTmp, len-2);

    bBufferTmp[6] = (char)(crc_16 & 0xFF);
    bBufferTmp[7] = (char)(crc_16 >> 8);

    //cp.Write(bBufferTmp); //Send packet

    //Thread.Sleep(msec_wait_rx);
    //foreach (char b in bBufferTmp)
    //    Console.Write(b.ToString("X2") + " ");
    //Console.WriteLine();
    qDebug() << "# " << bBufferTmp;

    // SendData(bBufferTmp, msec_wait_rx);

    //bBufferTmp = cp.Read(ref iReaderr, 7);

    /*
    if ( (bBufferTmp == null) || (bBufferTmp.Length != 7) || ((bBufferTmp[1] & 0x80) == 0x80) )
    {
        return;
    }
    foreach (byte b in bBufferTmp)
        Console.Write(b.ToString("X2") + " ");
    Console.WriteLine();
*/
    /*
    coils = (UInt16)((bBufferTmp[4] << 8) + bBufferTmp[3]);

    checkBoxEN_LOCK_A.Checked = ((coils & EN_LOCK_A) == 0x0000) ? false : true;
    checkBoxEN_LOCK_B.Checked = ((coils & EN_LOCK_B) == 0x0000) ? false : true;
    checkBoxEN_FAN_A1.Checked = ((coils & EN_FAN_A1) == 0x0000) ? false : true;
    checkBoxEN_FAN_A2.Checked = ((coils & EN_FAN_A2) == 0x0000) ? false : true;
    checkBoxEN_FAN_B1.Checked = ((coils & EN_FAN_B1) == 0x0000) ? false : true;
    checkBoxEN_FAN_B2.Checked = ((coils & EN_FAN_B2) == 0x0000) ? false : true;
    checkBoxEN_OUT1.Checked = ((coils & EN_OUT1) == 0x0000) ? false : true;
    checkBoxEN_OUT2.Checked = ((coils & EN_OUT2) == 0x0000) ? false : true;
    checkBoxSEL_UART2.Checked = ((coils & SEL_UART2) == 0x0000) ? false : true;
    */
    return Ambd002::Ok;
}



/**
  * Calcolo del CRC di tipo MODBUS RTU
  *
*/
qint16 Ambd002::crc16(char* bytes, int len)
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
