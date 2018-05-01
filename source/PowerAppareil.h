
#ifndef POWERAPPAREIL_H
#define POWERAPPAREIL_H
#include "PowerNode.h"

class PowerAppareil : public PowerNode {
protected:
    int proximiteSource;
public:
    PowerAppareil() {

    }

    void setProximite(int proximiteSource) {
        this->proximiteSource = proximiteSource;
    }

    void setKey(int key) {
        this->key = key;
    }

    int getKey() {
       return key;
    }
};

#endif
