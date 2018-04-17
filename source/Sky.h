/// \brief Gestion du ciel.
/// \details Permet de tourner le ciel et changer sa texture.
/// \author Mathilde Harnois
/// \date 12 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#include "includes.h"
class Sky : public Model {
private:
    bool isDayTime; ///< Booléen qui indique si c'est le jour ou la nuit
    double sphereAngle; ///< Angle de la sphère en fonction des axes x et y
    Matrix rotation; ///< Matrice de rotation du ciel
    //Chrono chrono;

public:

    /// Contructeur
    /// \param textureID Identificateur de la texture.
    /// \param objFile Nom du fichier depuis lequel charger le modèle, au format Wavefront (.obj).
    Sky(unsigned int textureID, const char* objFile = nullptr) : Model(textureID, objFile) {
        isDayTime = true;
        sphereAngle = .0;

        textureIDs["night"] =  ResourceManager::getInstance()->getTexture("nightsky");
    }

    /// Change la position de la sphère selon le temps écoulé dans une phase de jeu avec une rotation
    /// \param deltaTime Temps écoulé depuis le dernier calcul d'angle
    void update(float deltaTime) {
        //on considère qu'une phase dure 15 minutes, donc rotationne de 6 degrés par minutes (qu'on converti en microsecondes)
        if(sphereAngle >= 180) {
            isDayTime = false;
            textureToDraw = textureIDs["nightsky"];
        }
        else {
            if(sphereAngle >= 360) {
                isDayTime = true;
                sphereAngle = 0;
                textureToDraw = textureIDs["daysky"];

            }
            else {
                sphereAngle += deltaTime * (1.00 * pow(10, -7));
                rotation.loadZRotation(sphereAngle);
                transform(rotation);
            }
        }
    }

};


#endif
