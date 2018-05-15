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
    SIMCoinMiner(double usedCurrent, const std::string& name, double posx, double posy, double posz,  bool rotHitBox, const char* objFile = nullptr) : PowerDevice(usedCurrent, name, posx, posy, posz, 0, rotHitBox, objFile) {
        textureToDraw = EntityManager::get<Texture2d*>("simcoinminer")->ID;
        isInFunction = false;
        SIMCoinsGenerated = 0;

    }

    double setPowerIN(double power) {

      }
    double generateSIMCoins(){
        unsigned int ratio, magicNumber;
        ratio = 1000/usedCurrent;
        for (int i = 0; i < 10; i++){
            magicNumber = rand() % ratio;
            if(magicNumber == 1){
                SIMCoinsGenerated += 100;
            }
        }
    }

    void setCurrent(double current){
        usedCurrent = current;
    }

};

#endif
