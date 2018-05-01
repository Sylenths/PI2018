#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode /*: public Model*/ {
protected:
    double used;
    double generated;
    int key;
    int indice;
    std::map<int, std::list<int>> pathsMap;
    std::list<PowerNode*> wires;

public:
    PowerNode() {
        this->indice = 9999;
    }

    void addWire(PowerNode* wire) {
        wires.push_back(wire);
    }

    void pushBackPathsMap(int source, int keyPath) {
        pathsMap[source].push_back(keyPath);
    }

    void clearPathsMap() {
        pathsMap.clear();
    }

    void setIndice(int indice) {
        this->indice = indice;
    }

    int getIndice() {
        return indice;
    }

    virtual void setKey(int key) {};

    virtual int getKey() {};






};

#endif
