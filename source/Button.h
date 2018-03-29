/// \brief Représentation d'un bouton
/// \details Pour réagir au clic de souris et autre si possible
/// \author Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "Model.h"
#include "Image2D.h"

class Button : public Image2D{
private:
    std::function<void()> onClick;  ///< Le pointeur de méthode vers quoi on veut réagir avec nos événements

public:
	/// Constructeur.
	/// \param onClick Fonction Activée par le bouton.
    /// \param textureID Identificateur de la texture.
	/// \param x Position en x par rapport au coin gauche en haut.
	/// \param y Position en y par rapport au coin gauche en haut.
	/// \param width Largeur du bouton.
	/// \param height Hauteur du bouton.
    Button( unsigned int textureID, unsigned int x, unsigned int y, unsigned int z, double width, double height) : Image2D(textureID,x,y,z,width,height){

    }
	/// Réception de notifications d'événements SDL.
	/// \param sdlEvent Événement SDL.
    void notify(SDL_Event* sdlEvent) {
        if (sdlEvent->button.button == SDL_BUTTON_LEFT) {
            if (sdlEvent->button.x >= x) {
                if (sdlEvent->button.x <= (x + width)) {
                    if (sdlEvent->button.y >= y) {
                        if (sdlEvent->button.y <= (y + height)) {
                            onClick();
                        }
                    }
                }
            }
        }

    }

    /// Bind une méthode d'une certaine classe
    /// \param Pour binder une méthode d'une certaine classe utiliser : std::bind(&Class::function, object) PS: ne pas oublier &
    void setOnClick(std::function<void()> onClick) {
        this -> onClick = onClick;
    }

};


#endif
