#ifndef POWERMANAGER_H
#define POWERMANAGER_H
#include "includes.h"
#include "PowerSource.h"

class PowerManager : public Singleton<PowerManager> {
private:
    std::list<PowerSource*> sources;
public:
    PowerManager();

    void addSource(PowerSource* source) {
        sources.push_back(source);
    }
};

#endif
