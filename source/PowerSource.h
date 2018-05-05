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

    void updateCurrent(double current) {
        currentLeft = current;
    }

    void resetCurrent() {
        currentLeft = producedCurrent;
    }

    double getCurrentLeft() {
        return currentLeft;
    }
};

#endif
