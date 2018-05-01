#ifndef POWERSOURCE_H
#define POWERSOURCE_H
#include "PowerNode.h"

class PowerSource : public PowerNode {
private:
    double producedCurrent;
    double currentLeft;

public:
    PowerSource(double producedCurrent) {
        this->producedCurrent = producedCurrent;
        currentLeft = producedCurrent;
    }

    void usedCurrent(double used) {
        currentLeft -= used;
    }

    void resetCurrent() {
        currentLeft = producedCurrent;
    }
};

#endif
