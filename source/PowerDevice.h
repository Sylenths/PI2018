
#ifndef POWERAPPAREIL_H
#define POWERAPPAREIL_H
#include "PowerNode.h"

class PowerDevice : public PowerNode {
protected:
    int proximityIndice;
    double usedCurrent;
    double currentLeft;
    bool feeded;
    std::map<int, std::queue<int>>* pathsMap;
    int mapSize;
public:
    PowerDevice(double usedCurrent, const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : PowerNode(name, posx, posy, posz ,textureID, rotHitBox, objFile) {
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

    bool isFeeded() {
        return feeded;
    }

    void resetCurrent() {
        currentLeft = usedCurrent;
        feeded = false;
    }

    double updateCurrent(double currentIn) {
        currentLeft -= currentIn;
        if(currentLeft < 0.00) {
            feeded = true;
            sphere->setTexture("Green");
            return currentLeft * -1.0;

        }
        else {
            feeded = false;
            sphere->setTexture("Red");
            return 0.0;
        }
    }
};

#endif
