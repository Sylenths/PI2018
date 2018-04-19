/// \brief Action qui construit un mur
/// \details Classe héritant de action et qui contient tout les informations relatives à la création des mur
/// \author Shelby Versailles
/// \date 19 Avril 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SOURCE_BUILDWALL_H
#define SOURCE_BUILDWALL_H

#include "includes.h"

class BuildWall : public Action{
private:
    Materiel* materiel;
    unsigned int height;
    Fondation* start;
public:
    BuildWall(Materiel* materiel, unsigned int height, Fondation* start) {
        this->materiel = materiel;
        this->height = height;
        this->start = start;
    }
    Materiel* getMateriel(){
        return materiel;
    }
    unsigned int getHeight(){
        return height;
    }
    Fondation* getFondation(){
        return start;
    }

};
#endif //SOURCE_BUILDWALL_H
