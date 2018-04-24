#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode /*: public Model*/ {
private:
    double powerIN;
    double used;
    double generated;
    bool isAwire;
    std::list<PowerNode*> wires;

public:
    PowerNode() {

    }

    double getPowerOUT() {
        return (powerIN + generated - used) / wires.size();
    }

    void setPowerIN(double powerIN) {
        this->powerIN = powerIN;
    }

    void addWire(PowerNode* wire) {
        wires.push_back(wire);
    }


};

#endif
