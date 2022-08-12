#ifndef POS_H
#define POS_H

#include <QDebug>



class Pos
{
public:

    typedef enum _posType {
        POSTYPE_WINEPTS,    // Usa WinEPTS tipo COOP
        POSTYPE_USBSER,     // Seriale virtuale
        POSTYPE_PPP         // Comunicazione socket PPP
    } PosType;


    // Costruttore
    Pos( PosType posType = POSTYPE_USBSER);

    int posPay(float fValue);
    int posPay(int nEuroCent);

    int posEnable();
    int posDisable();
    int posReset();


private:
    PosType _posType;
    char    _posPort;

    // Parametri EPTS

    // Parametri POS

};

#endif // POS_H
