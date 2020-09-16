#ifndef POS_H
#define POS_H

#include <QDebug>



class pos
{
public:

    typedef enum _posType {
        POSTYPE_WINEPTS,
        POSTYPE_SER,
        POSTYPE_PPP
    } PosType;


    pos( PosType posType = POSTYPE_SER);

    int posPay(float fValue);
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
