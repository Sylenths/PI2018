#ifndef BATTERIE_H
#define BATTERIE_H
#include "PowerSource.h"
#include "PowerAppareil.h"

class Batterie : public PowerSource, public PowerAppareil {
public:
    Batterie();
};

#endif // BATTERIE_H
