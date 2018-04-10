/// \brief Représentation d'une case à cocher.
/// \details Case à cocher réagissant au clic de souris.
/// \author Antoine Legault
/// \date 10 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Le changement de texture ne fonctionne pas.

#ifndef SOURCE_CHECKBOX_H
#define SOURCE_CHECKBOX_H

#include "includes.h"

class CheckBox : public Image {
public:
    /// Constructeur.
    /// \param onClick Fonction appelée par un click de souris.
    /// \param textureID Identificateur de la texture.
    /// \param x Position en x par rapport au coin supérieur gauche de la fenêtre.
    /// \param y Position en y par rapport au coin supérieur gauche de la fenêtre.
    /// \param width Largeur du bouton.
    /// \param height Hauteur du bouton.
    CheckBox(double x, double y, double z, double width, double height, unsigned int defaultTextureID, unsigned int checkTextureID = 0) : Image(x, y, z, width, height, defaultTextureID) {
        textureIDs["clic"] =  (checkTextureID) ? checkTextureID : defaultTextureID;
        onClick = nullptr;
    }


    /// Réception de notification d'événement SDL.
    /// \param sdlEvent Événement SDL.
    void notify(SDL_Event* sdlEvent) {
        if ((sdlEvent->button.x >= vertices[0]) && (sdlEvent->button.x <= vertices[3]) &&
            (sdlEvent->button.y >= vertices[1]) && (sdlEvent->button.y <= vertices[4])) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick){
                        textureToDraw = textureIDs["clic"];
                        onClick();
                    }
                    break;

            }
        }
        else
            textureToDraw = textureIDs["default"];
    }

};


#endif
