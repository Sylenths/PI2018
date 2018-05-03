#ifndef POWERNODE_H
#define POWERNODE_H
#include "Model.h"
#include "includes.h"


class PowerNode /*: public Model*/ {
protected:
    int key;
    int indice;

public:
    PowerNode() {
        this->indice = 9999;
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
