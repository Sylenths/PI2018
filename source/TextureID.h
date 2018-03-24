/// \brief Permet de récupérer la numéro de la texture.
/// \details Permet de classer les textures.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_TEXTUREID_H
#define SOURCE_TEXTUREID_H

#include <string>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include "Resource.h"

class TextureID : public Resource{
private:
    unsigned int openGLID;      ///< Composante ID des textures.
    std::string description;    ///< Composante Description de la texture.
public:

    /// Récupérer l'ID de la texture.
    /// \param filename Le nom du fichier de la texture.
    unsigned int getID(const char* filename){
            glGenTextures(1, &openGLID);
            glBindTexture(GL_TEXTURE_2D, openGLID);

            SDL_Surface* surface = IMG_Load(filename);
            glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
            SDL_FreeSurface(surface);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            return openGLID;
    }

    /// Description de la texture.
    std::string getDescription(){

    }
};


#endif
