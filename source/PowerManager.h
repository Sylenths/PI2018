#ifndef POWERMANAGER_H
#define POWERMANAGER_H
#include "includes.h"
#include "PowerAppareil.h"

class PowerManager : public Singleton<PowerManager> {
private:
    std::list<PowerAppareil*> appareils;
public:
    PowerManager();

    void addSource(PowerAppareil* appareil) {
        appareils.push_back(appareil);
    }

    void resetPower() {

    }

    void updatePower() {

    }
};

#endif
