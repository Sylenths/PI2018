//
// Created by Mic on 2018-03-28.
//
/// \brief Classe qui crée une texture avec un texte
/// \details Contient une méthode statique qui ajoute une texture de texte au resourceManager
/// \author Mickaël Grisé-Roy
/// \date 28 mars 2018
/// \version 1.0
/// \warnings No warnings
/// \bug Dans createTextTextures le glFenTextures ne reaffectes pas le openGLID et donc, la texture n'est pas ajoutee au RM
#ifndef SOURCE_LABEL_H
#define SOURCE_LABEL_H

#include <string>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "ResourceManager.h"

class Label{
public:
    /// Ajoute la texture avec le texte dans le resourceManager
    /// \param La string qui servira de clé dans la texture
    /// \param Le texte qui sera texturisé
    /// \param La font utilisee
    /// \param La couleur du texte qui sera texturisé

    static void createTextTexture(std::string texNameRM, std::string text, TTF_Font* font, SDL_Color color){
        SDL_Surface* sdlSurface = TTF_RenderText_Blended(font , text.c_str(), color);
        unsigned int openGLID = 5;

        glGenTextures(1, &openGLID);
        glBindTexture(GL_TEXTURE_2D, openGLID);

        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        SDL_FreeSurface(sdlSurface);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ResourceManager::getInstance()->addTexture(texNameRM,openGLID);
    }


};
#endif //SOURCE_LABEL_H
