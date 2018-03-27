/// \brief Représentation d'un bouton
/// \details Pour réagir au clic de souris et autre si possible
/// \author Tai Chen Li
/// \date 25 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef BUTTON_H
#define BUTTON_H

#include "Model.h"

class Button : public Model{
private:

public:
    Button(Mesh* mesh, TextureID* textureID) : Model(mesh, textureID){

    }

    void notify(SDL_Event* sdlEvent) {

    }
};


#endif