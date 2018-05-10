/// \brief Contient la resistance le prix et la texture d'un matériel.
/// \author Shelby Versailles
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_MATERIEL_H
#define SOURCE_MATERIEL_H

#include "includes.h"

class Materiel {
private:

    std::string description;
public:
    unsigned int resistance, price, textureID, masse, pointDeRupture;
    Materiel( unsigned int resistance, unsigned int price, unsigned int masse, unsigned int pointDeRupture){
        this->price = price;
        this->resistance = resistance;
        this->masse = masse;
        this->pointDeRupture = pointDeRupture;
        description = "";
    }

    static Materiel* bois;
    static Materiel* carton;
    static Materiel* pierre;
    static Materiel* metal;
    static Materiel* simtium;
    static Materiel* cuivre;
    static Materiel* argent;

    std::string getDescription(){
        char buffer[10];
        SDL_itoa(resistance, buffer, 10);
        description += "Resistance: ";
        description += buffer;
        description += "\n";

        SDL_itoa(price, buffer, 10);
        description += "Prix: ";
        description +=  buffer;
        description += "\n";

        if(masse != 0){
            SDL_itoa(masse, buffer, 10);
            description += "Masse: ";
            description += buffer;
            description += "\n";
        }


        if(pointDeRupture != 0){
            SDL_itoa(pointDeRupture, buffer, 10);
            description += "Point de rupture: ";
            description += buffer;
            description += "\n";
        }


        return description;
    }
};

Materiel* Materiel::carton = new Materiel(5,1,2,5);
Materiel* Materiel::bois = new Materiel(4,2,3,4);
Materiel* Materiel::pierre = new Materiel(3,3,4,3);
Materiel* Materiel::metal = new Materiel(2,4,5,2);
Materiel* Materiel::simtium = new Materiel(1,1,1,5);
Materiel* Materiel::cuivre = new Materiel(5, 1, 0, 0);
Materiel* Materiel::argent = new Materiel(1, 5, 0, 0);

#endif //SOURCE_MATERIEL_H
