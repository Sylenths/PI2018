#ifndef POWERSOURCE_H
#define POWERSOURCE_H
#include "PowerNode.h"

class PowerSource : public PowerNode {
private:
    double producedCurrent;
public:
    PowerSource() {

    }
};

#endif
