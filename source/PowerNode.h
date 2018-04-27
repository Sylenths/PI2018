#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode /*: public Model*/ {
protected:
    double powerIN;
    double used;
    double generated;
    bool isASource;
    std::list<PowerNode*> wires;

public:
    PowerNode() {

    }

    void addWire(PowerNode* wire) {
        wires.push_back(wire);
    }

    virtual void setKey(int key) {};

    virtual int getKey() {};






};

#endif
