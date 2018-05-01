
#ifndef SOURCE_TEXTWINDOW_H
#define SOURCE_TEXTWINDOW_H

#include "includes.h"

class TextWindow : public Model{
private:
    std::string text;
    SDL_Surface* sdlSurface;
    int w;
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
    TextWindow(TTF_Font* font, SDL_Color color, std::string text, unsigned int x, unsigned int y, unsigned int z, unsigned int w, unsigned h, unsigned int textureID = 0) : Model(x, y, z, textureID, false) {
        this->text = text;
        this->w = w;
        this->x = x;
        this->y = y;
        cutTextForBox();
        sdlSurface = TTF_RenderText_Blended(font , text.c_str(), color);
        vertexCount = 6;
        vertices = new double[18]{
                (double) x,(double) y, 0.0,
                (double) (x + w), (double) y, 0.0,
                (double)x,(double) (y + sdlSurface->h), 0.0,

                (double)(x + w), (double)y, 0.0,
                (double)x, (double)y + sdlSurface->h, 0.0,
                (double)(x + w), (double)(y + sdlSurface->h), 0.0
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

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        textureIDs["default"] = textureToDraw;
    }

    void cutTextForBox(){
        char runner;
        int width = 0;
        for(int i = 0; i < text.length(); i++){
            runner = text[i];
            if(runner == '\n'){
                width = 0;
            }
            if(width >= w){
                text.insert(i, "\n");
            }
            width++;

        }


    }

    void updateTextTexture(std::string text, TTF_Font* font, SDL_Color color){
        sdlSurface = TTF_RenderText_Blended(font , text.c_str(), color);
        glDeleteTextures(1,&textureToDraw);
        glGenTextures(1, &textureToDraw);
        glBindTexture(GL_TEXTURE_2D, textureToDraw);
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        textureIDs["default"] = textureToDraw;
    }

    ~TextWindow(){
        SDL_FreeSurface(sdlSurface);
    }

};


#endif
