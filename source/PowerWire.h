#ifndef POWERWIRE_H
#define POWERWIRE_H
#include "PowerNode.h"

class PowerWire : public PowerNode {
private:
    PowerNode* node1;
    PowerNode* node2;
    double resistance;
public:
    PowerWire(PowerNode* node1, PowerNode* node2, double resistance) {
        isAWire = true;
        this->node1 = node1;
        this->node2 = node2;
        this->resistance = resistance;

        node1->addWire(this);
        node2->addWire(this);
    }


};

#endif
