/// \brief Représentation de tous les resources nécessaires au projet.
/// \details Classe virtuelle.
/// \author Antoine Legault, Tai Chen Li, Samuel Labelle
/// \date 24 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.
#ifndef RESOURCE_H
#define RESOURCE_H

class Resource{
private:

public:
    //virtual void nothing() = 0;

    /// Cette fonction permet de dessiner la ressource dans la fenêtre. ELLE POURRAIT ÊTRE REMPLACÉ PAR SON ENFANT. Sinon, draw() ne fait rien.

    virtual void draw() {}

};


#endif
