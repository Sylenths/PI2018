#ifndef POWERWIRE_H
#define POWERWIRE_H
#include "PowerNode.h"

class PowerWire : public PowerNode {
protected:
    PowerNode* node1;
    PowerNode* node2;
    double resistance;
    double lenght;
public:
    PowerWire(PowerNode* node1, PowerNode* node2, double resistance, double lenght) {
        this->node1 = node1;
        this->node2 = node2;
        this->resistance = resistance;
        this->lenght = lenght;

        node1->addWire(this);
        node2->addWire(this);
    }


};

#endif
