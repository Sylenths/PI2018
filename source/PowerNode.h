#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode /*: public Model*/ {
protected:
    int indice;
    double powerIN;
    double used;
    double generated;
    bool isASource;
    std::list<PowerNode*> wires;

public:
    PowerNode() {
        indice = 0;
    }

    void addWire(PowerNode* wire) {
        wires.push_back(wire);
    }

    virtual void setKey(int key) {};

    virtual int getKey() {};






};

#endif
