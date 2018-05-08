//
// Created by Mic on 2018-03-28.
//
/// \brief Classe représentant un étiquette.
/// \details Contient une méthode statique qui ajoute une texture de texte au resourceManager
/// \author Mickaël Grisé-Roy, Patrick Singcaster
/// \date 28 mars 2018
/// \version 0.2
/// \warning No warning
/// \bug Dans createTextTextures le glFenTextures ne reaffectes pas le openGLID et donc, la texture n'est pas ajoutee au RM
#ifndef SOURCE_LABEL_H
#define SOURCE_LABEL_H

#include "includes.h"

class Label : public Model {
private:
    int x;
    int y;
public:
    /// Ajoute la texture avec le texte dans le resourceManager
    /// \param font Police de caractères
    /// \param color Couleur du texte.
    /// \param text Texte affiché.
    /// \param x Position en x par rapport au coin supérieur gauche.
    /// \param y Position en y par rapport au coin supérieur gauche.
    /// \param width Largeur de l'image.
    /// \param height Hauteur de l'image.
    Label(const std::string& name, TTF_Font* font, SDL_Color color, std::string text, unsigned int x, unsigned int y, unsigned int z, unsigned int textureID = 0) : Model(name, x, y, z, textureID, false) {
        SDL_Surface* sdlSurface = TTF_RenderText_Blended(font , text.c_str(), color);
        vertexCount = 6;
        this->x = x;
        this->y = y;
        vertices = new double[18]{
                (double)x, (double)y, 0.0,
                (double)(x + sdlSurface->w), (double)y, 0.0,
                (double)x, (double)(y + sdlSurface->h), 0.0,

                (double)(x + sdlSurface->w), (double)y, 0.0,
                (double)x, (double)(y + sdlSurface->h), 0.0,
                (double)(x + sdlSurface->w), (double)(y + sdlSurface->h), 0.0
        };

        normals = new double[18]{
                0.0, 0.0 , 1.0,
                0.0, 0.0,  1.0,
                0.0, 0.0,  1.0,

                 0.0, 0.0 , 1.0,
                 0.0, 0.0,  1.0,
                 0.0, 0.0,  1.0
        };

        texCoords = new double [12]{
                0.0,  0.0,
                1.0,  0.0,
                0.0,  1.0,

                1.0,  0.0,
                 0.0,  1.0,
                 1.0,  1.0
        };



        glGenTextures(1, &textureToDraw);
        glBindTexture(GL_TEXTURE_2D, textureToDraw);
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

        SDL_FreeSurface(sdlSurface);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        textureIDs["default"] = textureToDraw;
    }

    void updateTextTexture(std::string text, TTF_Font* font, SDL_Color color){
        SDL_Surface* sdlSurface = TTF_RenderText_Blended(font , text.c_str(), color);

        vertices[3] = (double)(x + sdlSurface->w);
        vertices[7] = (double)(y + sdlSurface->h);
        vertices[9] = (double)(x + sdlSurface->w);
        vertices[13] = (double)(y + sdlSurface->h);
        vertices[15] =  (double)(x + sdlSurface->w);
        vertices[16] = (double)(y + sdlSurface->h);

        glDeleteTextures(1,&textureToDraw);
        glGenTextures(1, &textureToDraw);
        glBindTexture(GL_TEXTURE_2D, textureToDraw);
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        SDL_FreeSurface(sdlSurface);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        textureIDs["default"] = textureToDraw;
    }

};

#endif
