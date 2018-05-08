/// \brief Panneau solaire
/// \details Calcule l'énergie produit
/// \author Antoine Legault, Samuel Labelle, Guillaume Julien-Desmarchais
/// \date 27 mars 2018
/// \version 0.2
/// \warning getLightAngle ne renvoit pas la bonne angle
/// \bug le modele obj du panneau solaire cause un crash lorsque loader.
#ifndef PANNEAUSOLAIRE_H
#define PANNEAUSOLAIRE_H
#define ENERGYOUTPUT 20
#include "PowerSource.h"

class PanneauSolaire : public PowerSource {
public:
    PanneauSolaire(const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : PowerSource(0, name, posx, posy ,posz, textureID, rotHitBox, objFile){

    };

    /// Calcule l'angle entre le panneau solaire et le soleil
    /// \param sun Le vecteur du soleil
    /// \return L'angle entre le panneau solaire et le soleil.
    double getLightAngle(Vector sun) {
        Vector position, result;
        position = (posx, posy, posz);
        result = position - sun;
        double test = getAngle(result, {0.0,1.0,0.0});//2e vecteur est une normale du panneau solaire. 0.6868, 0.0740, 0.7231
        energyProduced(test);
    }


    /// Retourne l'angle entre 2 vecteurs
    /// \param a,b Les deux vecteurs
    double getAngle(Vector a, Vector b){
        return acos((a*b)/((a.getNorm()) * b.getNorm()));
    }


    /// Calcule l'énergie produite
    /// \param angle L'angle entre le soleil et la panneau solaire
    /// \return l'énergie produite
    double energyProduced(double angle){
        double multiplicator = ENERGYOUTPUT/90;
        double energy;

        if (angle < 90) {
            energy = angle * multiplicator;
        }
        else{
            multiplicator = multiplicator * -1.0;
            energy = angle * multiplicator + (ENERGYOUTPUT - (multiplicator * 90));
        }
        updateCurrent(energy);
    }

};

#endif
