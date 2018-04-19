/// \brief Contient la resistance le prix et la texture d'un matériel.
/// \author Shelby Versailles
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_MATERIEL_H
#define SOURCE_MATERIEL_H

class Materiel{
private:
    unsigned int resistance;
    unsigned int price;
    unsigned int textureID;
public:
    Materiel( unsigned int resistance, unsigned int price, unsigned int textureID){
        this->price = price;
        this->resistance = resistance;
        this->textureID = textureID;
    }
};


#endif //SOURCE_MATERIEL_H
