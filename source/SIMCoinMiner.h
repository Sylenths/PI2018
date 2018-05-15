/// \brief Gestion du SIMCoinMiner
/// \details Produit des SIMCoins en échange d'énergie.
/// \author Jade St-Pierre Bouchard
/// \date 26 Avril 2018
/// \version 0.1

#ifndef SIMCOINMINER_H
#define SIMCOINMINER_H
#include "PowerDevice.h"

class SIMCoinMiner : public PowerDevice {
private:
    bool isInFunction;
    int SIMCoinsGenerated;
public:
    SIMCoinMiner(double usedCurrent, const std::string& name, double posx, double posy, double posz, unsigned int textureID,  bool rotHitBox, const char* objFile = nullptr) : PowerDevice(usedCurrent, name, posx, posy, posz, textureID, rotHitBox, objFile) {
        /*isAsource = false;
        used = 0;
        generated = 0;
        powerIN = 0;
        */
        isInFunction = false;
        SIMCoinsGenerated = 0;

    }

    double setPowerIN(double power) {

      }
    double generateSIMCoins(){

    }
};

#endif
