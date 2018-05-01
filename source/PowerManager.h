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
        mapAppareil[appareilNbr] = appareil;

        for(int i = appareilNbr; i > sourceNbr; --i) {
            adjMatrice[std::make_pair(appareilNbr, i)] = nullptr;
            adjMatrice[std::make_pair(i, appareilNbr)] = nullptr;
        }
    }

    void removeAppareil(int key) {
        PowerNode* temp = mapAppareil[key];
        mapAppareil[key] = mapAppareil[appareilNbr];
        mapAppareil[key]->setKey(key);
        delete temp;

        for(int i = appareilNbr; i > sourceNbr; --i) {
            delete adjMatrice[std::make_pair(key, i)];
            adjMatrice[std::make_pair(key, i)] = adjMatrice[std::make_pair(appareilNbr, i)];
            delete adjMatrice[std::make_pair(i, key)];
            adjMatrice[std::make_pair(i, key)] = adjMatrice[std::make_pair(i, appareilNbr)];
        }
        appareilNbr--;
    }

    void removeSource(int key) {
        sourceNbr++;
        PowerNode* temp = mapSource[key];
        mapSource[key] = mapSource[sourceNbr];
        mapSource[key]->setKey(key);
        delete temp;

        for(int i = (sourceNbr); i <= appareilNbr; ++i) {
            delete adjMatrice[std::make_pair(key, i)];
            adjMatrice[std::make_pair(key, i)] = adjMatrice[std::make_pair(sourceNbr, i)];
            delete adjMatrice[std::make_pair(i, key)];
            adjMatrice[std::make_pair(i, key)] = adjMatrice[std::make_pair(i, sourceNbr)];
        }
    }

    void createWire(int node1, int node2, double lenght, double diameter, int material) {
        std::pair<int, int> key1 = std::make_pair(node1, node2);
        std::pair<int, int> key2 = std::make_pair(node2, node1);
        PowerWire* wire = new PowerWire(lenght, diameter, material);
        adjMatrice[key1] = wire;
        adjMatrice[key2] = wire;
    }

    void setIndice(int indice) {
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
            setIndice(indice + 1);
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


    void getShortestPath(PowerAppareil* from) {
        from->clearPathsMap();
        from->setIndice(0);
        setIndice(0);

        for(int i = (sourceNbr + 1); i <= 0; ++i) {
            if(mapSource[i]->getIndice() != 9999) {
                int indiceTmp = 9999;
                int currentKey = i;
                int nextKey;

                while(mapAppareil[currentKey] != from) {
                    for(int j = (sourceNbr + 1); j <= appareilNbr; ++j) {
                        if(adjMatrice[std::make_pair(currentKey, j)]) {
                            if((j <= 0) && (mapSource[j]->getIndice() < indiceTmp)) {
                                indiceTmp = mapSource[j]->getIndice();
                                nextKey = j;
                            }
                            if((j > 0) && (mapAppareil[j]->getIndice() < indiceTmp)) {
                                indiceTmp = mapAppareil[j]->getIndice();
                                nextKey = j;
                            }
                        }
                    }

                    from->pushBackPathsMap(i, currentKey);
                    currentKey = nextKey;
                }
            }

        }
        resetIndice();
        from->setProximite();
    }

    void updatePower() {
        std::list<std::pair<int, int>> listPriority;
        for(int i = 1; i <= appareilNbr; ++i) {
            getShortestPath(mapAppareil[i]);
            listPriority.push_back(std::make_pair(i, mapAppareil[i]->getProximite()));
        }




    }
};

#endif
