#ifndef BATTERIE_H
#define BATTERIE_H
#include "PowerSource.h"
#include "PowerDevice.h"

class Batterie : public PowerSource, public PowerDevice {
public:
    Batterie();
};

#endif // BATTERIE_H
