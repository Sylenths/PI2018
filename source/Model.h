/// \brief La maille est la somme de tous les points pour former une forme géométrique dans OpenGL.
/// \details
/// \author Tai Chen Li
/// \date 25 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef SOURCE_MODEL_H
#define SOURCE_MODEL_H

#include "Resource.h"
#include "Observer.h"
#include "TextureID.h"
#include "Mesh.h"

class Model : public Resource, public Observer<SDL_Event*>{
protected:
    Mesh* mesh;
	unsigned int textureID

public:
    Model(Mesh* mesh, TextureID* textureID = nullptr) {
        this -> mesh = mesh;
        if (textureID != nullptr)
            mesh->setTextureID(textureID);
    }

    virtual void notify(SDL_Event* sdlEvent) = 0;
    virtual void nothing() = 0;
    virtual void draw() = 0;
};


#endif //SOURCE_MODEL_H
