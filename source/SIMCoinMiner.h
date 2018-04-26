/// \brief Gestion du SIMCoinMiner
/// \details Produit des SIMCoins en échange d'énergie.
/// \author Jade St-Pierre Bouchard
/// \date 26 Avril 2018
/// \version 0.1

#ifndef SIMCOINMINER_H
#define SIMCOINMINER_H
#include "PowerAppareil.h"

class SIMCoinMiner : public PowerAppareil {
private:
    bool isInFunction;
    int SIMCoinsGenerated;
public:
    SIMCoinMiner() {
        isAsource = false;
        used = 0;
        generated = 0;
        powerIN = 0;
        isInfunction = false;
        SIMCoinsGenerated = 0;

    }

    double setPowerIN(double power) {
      }
    double generateSIMCoins(){
    }
};

#endif
