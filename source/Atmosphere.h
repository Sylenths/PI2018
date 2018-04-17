/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et sa couleur
/// \author Mathilde Harnois
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#include "includes.h"

class Atmosphere : public Model {
private:

public:

    Atmosphere(unsigned int textureID, const char* objFile = nullptr) : Model(textureID, objFile) {

    }

};


#endif
