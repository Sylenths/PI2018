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

class Label : public Image2D{
private:
    std::string text;

public:
    /// Ajoute la texture avec le texte dans le resourceManager
    /// \param La font utilisee
    /// \param La couleur du texte qui sera texturisé
    /// \param Le texte qui sera texturisé
    /// \param La x position
    /// \param La y position
    /// \param La z position
    /// \param La width
    /// \param La height



    Label(TTF_Font* font,SDL_Color color, std::string text, unsigned int x, unsigned int y, unsigned int z, unsigned int w, unsigned int h) : Image2D(0,x,y,z,w,h){
        this->text = text;
        SDL_Surface* sdlSurface = TTF_RenderText_Blended(font , text.c_str(), color);

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
#endif //SOURCE_LABEL_H
