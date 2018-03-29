/// \brief Représentation d'un bouton
/// \details Pour réagir au clic de souris et autre si possible
/// \author Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef BUTTON_H
#define BUTTON_H

#include "Model.h"

class Button : public Model{
private:
    void (*onClick)();  ///< Le pointeur de fonction vers quoi on veut réagir avec nos événements

public:
	/// Constructeur.
	/// \param onClick Fonction Activée par le bouton.
    /// \param textureID Identificateur de la texture.
	/// \param x Position en x par rapport au coin gauche en haut.
	/// \param y Position en y par rapport au coin gauche en haut.
	/// \param width Largeur du bouton.
	/// \param height Hauteur du bouton.
    Button(void (*onClick)(), unsigned int textureID, unsigned int x, unsigned int y, unsigned int z, double width, double height) : Model(textureID){
        this -> x = x;
        this -> y = y;
        this -> z = z;

        this -> width = width;
        this -> height = height;

        setOnClick(onClick);

        vertexCount = normalCount = texCount = 6;

        vertices = new double[vertexCount * 3] {

                0.0 + x  , 0.0 + y   , 0.0, //P1T1F1
                width + x, height + y, 0.0, //P2T1F1
                0.0 + x  , height + y, 0.0, //P3T1F1

                0.0 + x  , 0.0 + y   , 0.0, //P1T2F1
                width + x, 0.0 + y   , 0.0, //P2T2F1
                width + x, height + y, 0.0, //P3T2F1
        };

        normals = new double[normalCount * 3] {
                0.0, 0.0, 1.0, //P1T1F1
                0.0, 0.0, 1.0, //P2T1F1
                0.0, 0.0, 1.0, //P3T1F1

                0.0, 0.0, 1.0, //P1T2F1
                0.0, 0.0, 1.0, //P2T2F1
                0.0, 0.0, 1.0, //P3T2F1
        };

        texCoords = new double[texCount * 2] {
                0.0,0.0,
                1.0,1.0,
                0.0,1.0,
                0.0,0.0,
                1.0,0.0,
                1.0,1.0,
        };
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

    /// Configurer le pointeur de fonction vers la bonne fonction
    /// \param La fonction vers laquelle on veut que le bouton pointe.
    void setOnClick(void (*onClick)()) {
        this -> onClick = onClick;
    }

};


#endif
