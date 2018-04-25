#ifndef POWERMANAGER_H
#define POWERMANAGER_H
#include "includes.h"
#include "PowerWire.h"
#include "PowerAppareil.h"
#include "PowerSource.h"

class PowerManager : public Singleton<PowerManager> {
private:
    std::map<std::pair<int, int>, PowerWire*> adjMatrice;
    std::map<int, PowerAppareil*> mapAppareil;
    std::map<int, PowerSource*> mapSource;
    int appareilNbr, sourceNbr;
public:
    PowerManager() {
        appareilNbr = 0;
        sourceNbr = 0;
    }

    void addSource(PowerSource* source) {
        mapSource[sourceNbr] = source;
        for(int i = sourceNbr; i <= appareilNbr; ++i) {
            std::pair<int, int> key1 = std::make_pair(sourceNbr, i);
            adjMatrice[key1] = nullptr;
            std::pair<int, int> key2 = std::make_pair(i, sourceNbr);
            adjMatrice[key2] = nullptr;
        }
        sourceNbr--;
    }

    void addAppareil(PowerAppareil* appareil) {
        appareilNbr++;
        mapAppareil[appareilNbr] = appareil;
        for(int i = appareilNbr; i >= sourceNbr; --i) {
            std::pair<int, int> key1 = std::make_pair(appareilNbr, i);
            adjMatrice[key1] = nullptr;
            std::pair<int, int> key2 = std::make_pair(i, appareilNbr);
            adjMatrice[key2] = nullptr;
        }
    }

    void addWire(int node1, int node2, PowerWire* wire) {
        std::pair<int, int> key1 = std::make_pair(node1, node2);
        std::pair<int, int> key2 = std::make_pair(node2, node1);
        adjMatrice[key1] = wire;
        adjMatrice[key2] = wire;
    }

    void setAppareilPriority() {
        for(int i = 1; i <= appareilNbr; ++i) {

        }
    }

    void updatePower() {

    }
};

#endif
