
#ifndef POWERAPPAREIL_H
#define POWERAPPAREIL_H
#include "PowerNode.h"

class PowerAppareil : public PowerNode {
protected:
    int proximityIndice;
    double usedCurrent;
    double currentLeft;
    bool feeded;
    std::map<int, std::queue<int>>* pathsMap;
    int mapSize;
public:
    PowerAppareil(double usedCurrent, const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : PowerNode(name, posx, posy, posz ,textureID, rotHitBox, objFile) {
        this->usedCurrent = usedCurrent;
        usedCurrent = currentLeft;
        mapSize = 0;
        feeded = false;
        pathsMap = new std::map<int, std::queue<int>>();
    }

    std::map<int, std::queue<int>>* getPathMap() {
        return pathsMap;
    }

    void clearPathsMap() {
        (*pathsMap).clear();

    }

    int getProximite() {
        return proximityIndice;
    }

    bool isFeeded() {
        return feeded;
    }

    double updateCurrent(double currentIn) {
        currentLeft -= currentIn;
        if(currentLeft < 0.00) {
            feeded = true;
            return currentLeft * -1.0;
        }
        else {
            feeded = false;
            return 0.0;
        }
    }
};

#endif
