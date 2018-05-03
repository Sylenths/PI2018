/// \brief Représentation d'une case à cocher.
/// \details Case à cocher réagissant au clic de souris.
/// \author Antoine Legault
/// \date 10 avril 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_CHECKBOX_H
#define SOURCE_CHECKBOX_H

#include "includes.h"

class CheckBox : public Image {
protected:
    bool checked;
    bool MouseOver;
public:



    /// Constructeur.
    /// \param x Position en x par rapport au coin supérieur gauche de la fenêtre.
    /// \param y Position en y par rapport au coin supérieur gauche de la fenêtre.
    /// \param z Position en z par rapport au coin supérieur gauche de la fenêtre.
    /// \param width Largeur du bouton.
    /// \param height Hauteur du bouton.
    /// \param defaultTextureID La texture de base affichée sur le bouton.
    /// \param checkTextureID La seconde texture affichée qui sera changée lors d'un clic de souris.
    CheckBox(double x, double y, double z, double width, double height, unsigned int defaultTextureID, unsigned int checkTextureID) : Image(x, y, z, width, height, defaultTextureID) {
        textureIDs["clic"] =  (checkTextureID) ? checkTextureID : defaultTextureID;
        onClick = nullptr;
        checked = false;
        MouseOver = false;
    }
    void check(){
        checked = true;
        textureToDraw = textureIDs["clic"];
    }

    void uncheck(){
            checked = false;
            textureToDraw = textureIDs["default"];

    }

    bool getMouseOver(){
        return MouseOver;
    }


    /// Réception de notification d'événement SDL.
    /// \param sdlEvent Événement SDL.
    void notify(SDL_Event* sdlEvent) {
        if ((sdlEvent->button.x >= vertices[0]) && (sdlEvent->button.x <= vertices[3]) &&
            (sdlEvent->button.y >= vertices[1]) && (sdlEvent->button.y <= vertices[4])) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick){
                        if(textureToDraw == textureIDs["default"])
                            check();
                        else
                           check();
                        onClick();
                    }break;

                case SDL_MOUSEMOTION:
                        MouseOver = true;

                    break;

            }
        }
        else
            MouseOver = false;
    }

};


#endif
