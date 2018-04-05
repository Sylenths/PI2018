/// \brief Représentation de tous les resources nécessaires au projet.
/// \details Classe virtuelle.
/// \author Antoine Legault, Tai Chen Li, Samuel Labelle
/// \date 24 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.
#ifndef RESOURCE_H
#define RESOURCE_H
 #include "includes.h"

class Resource{
private:

public:


    /// Cette fonction permet de dessiner la ressource dans la fenêtre. ELLE POURRAIT ÊTRE REMPLACÉ PAR SON ENFANT. Sinon, draw() ne fait rien.

    virtual void draw() {}
    /// Cette methode retourne le pointeur de TTF_Font lorsque demande. La classe Font a aussi une methode getFont().
    virtual TTF_Font* getFont(){

    }
};


#endif
