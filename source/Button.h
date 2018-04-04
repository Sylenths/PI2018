/// \brief Représentation d'un bouton.
/// \details Bouton réagissant au clic de souris.
/// \author Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef BUTTON_H
#define BUTTON_H

#include "Image2D.h"

class Button : public Image2D {
public:

    std::function<void()> onClick;  ///< Pointeur de méthode réagissant à un click de souris.

    /// Constructeur.
    /// \param onClick Fonction activée par un click de souris.
    /// \param textureID Identificateur de la texture.
    /// \param x Position en x par rapport au coin supérieur gauche de la fenêtre.
    /// \param y Position en y par rapport au coin supérieur gauche de la fenêtre.
    /// \param width Largeur du bouton.
    /// \param height Hauteur du bouton.
    Button( unsigned int textureID, unsigned int x, unsigned int y, unsigned int z, double width, double height) : Image2D(textureID, x, y, z, width, height) {
        onClick = nullptr;
    }

    /// Réception de notification d'événement SDL.
    /// \param sdlEvent Événement SDL.
    void notify(SDL_Event* sdlEvent) {
        if (sdlEvent->button.button == SDL_BUTTON_LEFT)
            if ((sdlEvent->button.x >= x) && (sdlEvent->button.x <= (x + width)) && (sdlEvent->button.y >= y) && (sdlEvent->button.y <= (y + height)))
                if (onClick)
                    onClick();
    }
};

#endif
