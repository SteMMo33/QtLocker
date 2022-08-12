#include "pos.h"


/**
 * @brief pos::pos
 * @param posType
 * Costruttore
 */
Pos::Pos(PosType posType) : _posType(posType)
{
    qDebug() << "[pos] C'tor";
}



int Pos::posEnable()
{
    qDebug() << "[pos] Enable";
    return 1;
}



int Pos::posDisable()
{
    qDebug() << "[pos] Disable";
    return 1;
}


int Pos::posPay(int nEuroCent)
{
    qDebug() << "[pos] Pay " << nEuroCent;
    return 1;
}
