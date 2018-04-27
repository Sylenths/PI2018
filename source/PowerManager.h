#ifndef POWERMANAGER_H
#define POWERMANAGER_H
#include "includes.h"
#include "PowerWire.h"
#include "PowerPair.h"
#include "PowerSource.h"

class PowerManager : public Singleton<PowerManager> {
private:
    std::map<std::pair<int, int>, PowerWire*> adjMatrice;
    std::map<int, PowerPair*> mapAppareil;
    std::map<int, PowerPair*> mapSource;

    int appareilNbr, sourceNbr;
public:
    PowerManager() {
        appareilNbr = 0;
        sourceNbr = 0;
    }

    void addSource(PowerSource* source) {
        mapSource[sourceNbr] = new PowerPair(source);
        source->setKey(sourceNbr);

        for(int i = sourceNbr; i <= appareilNbr; ++i) {
            adjMatrice[std::make_pair(sourceNbr, i)] = nullptr;
            adjMatrice[std::make_pair(i, sourceNbr)] = nullptr;
        }
        sourceNbr--;
    }

    void addAppareil(PowerAppareil* appareil) {
        appareilNbr++;
        appareil->setKey(appareilNbr);
        mapAppareil[appareilNbr] = new PowerPair(appareil);

        for(int i = appareilNbr; i > sourceNbr; --i) {
            adjMatrice[std::make_pair(appareilNbr, i)] = nullptr;
            adjMatrice[std::make_pair(i, appareilNbr)] = nullptr;
        }
    }

    void removeAppareil(int key) {
        PowerPair* temp = mapAppareil[key];
        mapAppareil[key] = mapAppareil[appareilNbr];
        mapAppareil[key]->setKey(key);
        delete temp;

        for(int i = appareilNbr; i > sourceNbr; --i) {
            adjMatrice[std::make_pair(key, i)] = adjMatrice[std::make_pair(appareilNbr, i)];
            adjMatrice[std::make_pair(i, key)] = adjMatrice[std::make_pair(i, appareilNbr)];
        }
        appareilNbr--;
    }

    void removeSource(int key) {
        sourceNbr++;
        PowerPair* temp = mapSource[key];
        mapSource[key] = mapSource[sourceNbr];
        mapSource[key]->setKey(key);
        delete temp;

        for(int i = (sourceNbr); i <= appareilNbr; ++i) {
            adjMatrice[std::make_pair(key, i)] = adjMatrice[std::make_pair(sourceNbr, i)];
            adjMatrice[std::make_pair(i, key)] = adjMatrice[std::make_pair(i, sourceNbr)];
        }
    }

    void connectWire(int node1, int node2, PowerWire* wire) {
        std::pair<int, int> key1 = std::make_pair(node1, node2);
        std::pair<int, int> key2 = std::make_pair(node2, node1);
        adjMatrice[key1] = wire;
        adjMatrice[key2] = wire;
    }

    void SetIndice(int indice) {
        bool indiceAltered = false;
        for(int i = (sourceNbr + 1); i <= appareilNbr; ++i) {
            if((i <= 0) && (mapSource[i]->getIndice() == indice)) {
                int key = mapSource[i]->getKey();
                for(int j = sourceNbr + 1; j <= appareilNbr; ++j) {
                    if(adjMatrice[std::make_pair(key, j)]) {
                        if((j <= 0) && (mapSource[j]->getIndice() == 9999)) {
                            mapSource[j]->setIndice(indice + 1);
                            indiceAltered = true;
                        }
                        if((j > 0) && (mapAppareil[j]->getIndice() == 9999)) {
                            mapAppareil[j]->setIndice(indice + 1);
                            indiceAltered = true;
                        }
                    }
                }
            }
            if((i > 0) && (mapAppareil[i]->getIndice() == indice)) {
                int key = mapAppareil[i]->getKey();
                for(int j = sourceNbr + 1; j <= appareilNbr; ++j) {
                    if(adjMatrice[std::make_pair(key, j)]) {
                        if((j <= 0) && (mapSource[j]->getIndice() == 9999)) {
                            mapSource[j]->setIndice(indice + 1);
                            indiceAltered = true;
                        }
                        if((j > 0) && (mapAppareil[j]->getIndice() == 9999)) {
                            mapAppareil[j]->setIndice(indice + 1);
                            indiceAltered = true;
                        }
                    }
                }
            }
        }
        if(indiceAltered)
            SetIndice(indice + 1);
        else
            return;
    }

    void resetIndice() {
        for(int i = (sourceNbr + 1); i <= appareilNbr; ++i) {
            if(i <= 0) {
                mapSource[i]->setIndice(9999);
            }
            else {
                mapAppareil[i]->setIndice(9999);
            }
        }
    }


    void getShortestPath() {

    }

    void updatePower() {

    }
};

#endif
