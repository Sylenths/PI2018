
#ifndef POWERAPPAREIL_H
#define POWERAPPAREIL_H
#include "PowerNode.h"

class PowerAppareil : public PowerNode {
protected:
    int proximityIndice;
    double usedCurrent;
    double currentLeft;
public:
    PowerAppareil(double usedCurrent) {
        this->usedCurrent = usedCurrent;
        usedCurrent = currentLeft;
    }

    void setProximite() {
        proximityIndice = 0;
        for(std::map<int, std::stack<int>>::iterator it = pathsMap.begin(); it != pathsMap.end(); it++) {
            proximityIndice += (*it).second.size();
        }
    }

    int getProximite() {
        return proximityIndice;
    }

    double getCurrentLeft() {
        return currentLeft;
    }
};

#endif
