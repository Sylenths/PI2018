/// \brief Représentation d'une image 2D.
/// \details Crée un modèle 3D plat pour y recevoir une texture ou une image.
/// \author Gabriel Bourdages, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef IMAGE2D_H
#define IMAGE2D_H

#include "Model.h"
#include "Matrix.h"
#include "includes.h"

class Image2D : public Model {
private:
public:
    /// Constructeur.
    /// \param textureID Identificateur de la texture.
    /// \param x Position en x par rapport au coin gauche en haut.
    /// \param y Position en y par rapport au coin gauche en haut.
    /// \param width Largeur de l'image.
    /// \param height Hauteur de l'image.
    Image2D(unsigned int textureID, unsigned int x, unsigned int y, unsigned int z, double width, double height) : Model(textureID) {

        this -> x = x;
        this -> y = y;
        this -> z = z;

        vertexCount = normalCount = texCount = 6;

        vertices = new double[vertexCount * 3] {

                0.0 + x  , 0.0 + y   , z, //P1T1F1
                width + x, height + y, z, //P2T1F1
                0.0 + x  , height + y, z, //P3T1F1

                0.0 + x  , 0.0 + y   , z, //P1T2F1
                width + x, 0.0 + y   , z, //P2T2F1
                width + x, height + y, z, //P3T2F1
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
    void notify(SDL_Event* sdlEvent) {}



};


#endif
