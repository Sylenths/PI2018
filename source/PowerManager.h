#ifndef POWERMANAGER_H
#define POWERMANAGER_H
#include "includes.h"
#include "PowerWire.h"

class PowerManager : public Singleton<PowerManager> {
private:
    std::map<std::pair<int, int>, PowerWire*> adjMatrice;
public:
    PowerManager();

    void addSource() {

    }

    void addAppareil() {

    }

    void resetPower() {

    }

    void updatePower() {

    }
};

#endif
