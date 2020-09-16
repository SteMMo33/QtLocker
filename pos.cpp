#include "pos.h"


/**
 * @brief pos::pos
 * @param posType
 * Costruttore
 */
pos::pos(PosType posType) : _posType(posType)
{
    qDebug() << "[pos] C'tor";
}



int pos::posEnable()
{
    qDebug() << "[pos] Enable";
    return 1;
};



int pos::posDisable()
{
    qDebug() << "[pos] Disable";
    return 1;
};
