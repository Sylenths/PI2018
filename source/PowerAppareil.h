
#ifndef POWERAPPAREIL_H
#define POWERAPPAREIL_H
#include "PowerNode.h"

class PowerAppareil : public PowerNode {
protected:
    int proximityIndice;
    double usedCurrent;
    double currentLeft;
    bool feeded;
    std::map<int, std::stack<int>> pathsMap;
    int mapSize;
public:
    PowerAppareil(double usedCurrent) {
        this->usedCurrent = usedCurrent;
        usedCurrent = currentLeft;
        mapSize = 0;
        feeded = false;
    }

    void pushBackPathsMap(int source, int keyPath) {
        pathsMap[source].push(keyPath);

    }



    void clearPathsMap() {
        pathsMap.clear();

    }

    void setProximite() {
        proximityIndice = 0;
        //for(std::map<int, std::stack<int>>::iterator it = pathsMap.begin(); it != pathsMap.end(); it++) {
        //    proximityIndice += (*it).second.size();
        //}
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
