/// \brief Représentation d'un bouton.
/// \details Bouton réagissant au clic de souris.
/// \author Tai Chen Li, Samuel Labelle, Patrick Singcaster
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Model {
public:
    std::function<void()> onClick;  ///< Pointeur de méthode réagissant à un click de souris.

    /// Constructeur.
    /// \param onClick Fonction appelée par un click de souris.
    /// \param textureID Identificateur de la texture.
    /// \param x Position en x par rapport au coin supérieur gauche de la fenêtre.
    /// \param y Position en y par rapport au coin supérieur gauche de la fenêtre.
    /// \param width Largeur du bouton.
    /// \param height Hauteur du bouton.
    Button(unsigned int textureID, double x, double y, double z, double width, double height) : Model(textureID) {
        texCount = 12;
        vertexCount = normalCount = 18;

        vertices = new double[18] { x, y, z, width + x, height + y, z, x, height + y, z, x, y, z, width + x, y, z, width + x, height + y, z };
        normals = new double[18] { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 };
        texCoords = new double[12] { 0.0,0.0, 1.0,1.0, 0.0,1.0, 0.0,0.0, 1.0,0.0, 1.0,1.0 };

        onClick = nullptr;
    }

    /// Réception de notification d'événement SDL.
    /// \param sdlEvent Événement SDL.
    void notify(SDL_Event* sdlEvent) {
        if (sdlEvent->button.button == SDL_BUTTON_LEFT)
            if ((sdlEvent->button.x >= vertices[0]) && (sdlEvent->button.x <= vertices[3]) &&
                (sdlEvent->button.y >= vertices[1]) && (sdlEvent->button.y <= vertices[4]))
                if (onClick)
                    onClick();
    }
};

#endif
