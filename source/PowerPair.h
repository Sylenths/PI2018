#ifndef POWERPAIR_H
#define POWERPAIR_H
#include "PowerAppareil.h"
#include "includes.h"

class PowerPair {
protected:
    PowerAppareil* appareil;
    std::map<int, std::queue<int>>* pathsMap;
public:
    PowerPair(PowerAppareil* appareil) {
        this->appareil = appareil;
    }

    void setKey(int key) {
        appareil->setKey(key);
    }

    std::map<int, std::queue<int>>* getPathsMap() {
        return pathsMap;
    }


};

#endif
