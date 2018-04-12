/// \brief Gestion des éléments de l'atmosphère.
/// \details Permet de modifier l'atmosphère du jeu
/// \author Mathilde Harnois
/// \date 12 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#include "includes.h"

class Atmosphere : public World {
private:


    bool isDayTime; ///< Booléen qui indique si c'est le jour ou la nuit
    unsigned float sphereAngle; ///< Angle de la sphère en fonction des axes x et y
    Matrix rotation;

public:
    Atmosphere(unsigned int temperature, unsigned int sunPower, unsigned int simCoin, unsigned int buildingTime, Vector wind) : World(temperature, sunPower, simCoin, buildingTime, wind) {
        isDayTime = true;
        sphereAngle = .0;
    }

    /// Change la texture de la sphère selon le jour ou la nuit
    void changeTime() {

    }

    /// Change la position de la sphère selon le temps écoulé dans une phase de jeu avec une rotation
    /// \param phaseTime Temps écoulé depuis le début de la phase de jeu
    void rotateSphere(unsigned float phaseTime) {
        //on considère qu'une phase dure 15 minutes, donc rotationne de 6 degrés par minutes (qu'on converti en microsecondes)
        rotation.loadZRotation(phaseTime * (1.00 * pow(10, -7)));
        modelMap
    }


};


#endif
