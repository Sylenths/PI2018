#ifndef POWERRUNNER_H
#define POWERRUNNER_H
#include "PowerNode.h"


class PowerRunner {
private:
    double power;
    PowerNode* node;
public:
    PowerRunner(PowerNode* node) {
        this->node = node;
    }
};

#endif
