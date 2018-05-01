#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode /*: public Model*/ {
protected:
    int key;
    int indice;
    std::map<int, std::stack<int>> pathsMap;

public:
    PowerNode() {
        this->indice = 9999;
    }

    void pushBackPathsMap(int source, int keyPath) {
        pathsMap[source].push(keyPath);
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

    void setKey(int key) {
        this->key = key;
    }

    int getKey() {
        return key;
    }






};

#endif
