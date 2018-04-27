#ifndef POWERPAIR_H
#define POWERPAIR_H
#include "PowerAppareil.h"
#include "includes.h"

class PowerPair {
protected:
    PowerNode* node;
    int indice;
    std::map<int, std::queue<int>>* pathsMap;
public:
    PowerPair(PowerNode* node) {
        this->node = node;
        indice = 9999;
    }

    PowerNode* getAppareil() {
        return node;
    }

    void setKey(int key) {
        node->setKey(key);
    }

    int getKey() {
        return node->getKey();
    }

    std::map<int, std::queue<int>>* getPathsMap() {
        return pathsMap;
    }

    void setIndice(int indice) {
        this->indice = indice;
    }

    int getIndice() {
        return indice;
    }

};

#endif
