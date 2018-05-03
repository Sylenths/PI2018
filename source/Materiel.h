/// \brief Contient la resistance le prix et la texture d'un matériel.
/// \author Shelby Versailles
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_MATERIEL_H
#define SOURCE_MATERIEL_H

#include "ResourceManager.h"
#include "ProjetFinal.h"

class Materiel{
private:
    unsigned int resistance, price, textureID, masse, pointDeRupture;
    std::string description;
public:
    Materiel( unsigned int resistance, unsigned int price, unsigned int masse, unsigned int pointDeRupture, unsigned int textureID){
        this->price = price;
        this->resistance = resistance;
        this->textureID = textureID;
        this->masse = masse;
        this->pointDeRupture = pointDeRupture;
        description = "";
    }

    static Materiel* bois;
    static Materiel* carton;
    static Materiel* pierre;
    static Materiel* metal;
    static Materiel* simtium;

    std::string getDescription(){
        description += "Résistance:";
        description += resistance;
        description += "\n";

        description += "Prix:";
        description +=  price;
        description += "\n";

        description += "Masse:";
        description += masse;
        description += "\n";

        description += "Point de rupture:";
        description += pointDeRupture;
        description += "\n";
    }
};

Materiel* Materiel::carton = new Materiel(5,1,2,5,ResourceManager::getInstance()->getTexture("bambou"));
Materiel* Materiel::bois = new Materiel(4,2,3,4,ResourceManager::getInstance()->getTexture("bambou"));
Materiel* Materiel::pierre = new Materiel(3,3,4,3,ResourceManager::getInstance()->getTexture("bambou"));
Materiel* Materiel::metal = new Materiel(2,4,5,2,ResourceManager::getInstance()->getTexture("bambou"));
Materiel* Materiel::simtium = new Materiel(1,1,1,5,ResourceManager::getInstance()->getTexture("bambou"));


#endif //SOURCE_MATERIEL_H
