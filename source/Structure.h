/// \brief Classe mère de d'autre classe
/// \author Shelby Versailles
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.
#ifndef SOURCE_STRUCTURE_H
#define SOURCE_STRUCTURE_H

#include "includes.h"

class Structure : public Model{
private:
    Materiel* materiel;
public:
    Structure(Materiel* materiel, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Model(posx, posy, posz, textureID, rotHitBox, objFile){
        this->materiel = materiel;
    }
};

#endif
