#ifndef POWERWIRE_H
#define POWERWIRE_H
#include "PowerNode.h"

class PowerWire {
protected:
    double resistance;
    double lenght;
    double diameter;
    int material;
public:
    PowerWire(double lenght, double diameter, int material) {
        this->lenght = lenght;
        this->material = material;
        this->diameter = diameter;

        switch (material) {
        case 1:
            this->resistance = (0.000000016 * lenght) / (M_PI * (diameter / 2.0) * (diameter / 2.0));
            break;
        default:
            break;
        }
    }


};

#endif
