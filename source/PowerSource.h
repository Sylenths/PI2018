#ifndef POWERSOURCE_H
#define POWERSOURCE_H
#include "PowerNode.h"

class PowerSource : public PowerNode {
private:
    double producedCurrent;
    int key;
public:
    PowerSource() {

    }

    void setKey(int key) {
        this->key = key;
    }

    int getKey() {
        return key;
    }


};

#endif
