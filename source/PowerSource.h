#ifndef POWERSOURCE_H
#define POWERSOURCE_H
#include "PowerNode.h"

class PowerSource : public PowerNode {
private:
    double producedCurrent;
    double currentLeft;

public:
    PowerSource(double producedCurrent, const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : PowerNode(name, posx, posy, posz, textureID, rotHitBox, objFile) {
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
