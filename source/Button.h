/// \brief Représentation d'un bouton
/// \details Pour réagir au clic de souris et autre si possible
/// \author Tai Chen Li
/// \date 25 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef BUTTON_H
#define BUTTON_H

#include "Model.h"

class Button : public Model{
private:
    void (*onClick)();  ///< Le pointeur de fonction vers quoi on veut réagir avec nos événements

public:
    Button(void (*onClick)(), std::string textureName, unsigned int x, unsigned int y, double width = 0, double height = 0) : Model(textureName){
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

    void notify(SDL_Event* sdlEvent) { /*
        if (sdlEvent->key.keysym.sym == SDL_MOUSEBUTTONDOWN)
            if (sdlEvent->)

            */
    }

    /// Configurer le pointeur de fonction vers la bonne fonction
    /// \param La fonction vers laquelle on veut que le bouton pointe.
    void setOnClick(void (*onClick)()) {
        this -> onClick = onClick;
    }

};


#endif