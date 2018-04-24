#ifndef POWERAPPAREIL_H
#define POWERAPPAREIL_H
#include "PowerNode.h"

class PowerAppareil : public PowerNode {
protected:
    unsigned int proximiteSource;
public:
    PowerAppareil();
};

#endif
