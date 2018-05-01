/// \brief Représentation d'un bouton.
/// \details Bouton réagissant au clic de souris.
/// \author Tai Chen Li, Samuel Labelle, Patrick Singcaster
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Image {
public:
    /// Constructeur.
    /// \param x Position en x par rapport au coin supérieur gauche de la fenêtre.
    /// \param y Position en y par rapport au coin supérieur gauche de la fenêtre.
    /// \param z Position en z par rapport au coin supérieur gauche de la fenêtre.
    /// \param width Largeur du bouton.
    /// \param height Hauteur du bouton.
    /// \param defaultTextureID La texture de base affichée sur le bouton.
    /// \param mouseOverTextureID La texture affichée sur le bouton lorsqu'on le survole avec la souris.
    Button(double x, double y, double z, double width, double height, unsigned int defaultTextureID,
           unsigned int mouseOverTextureID = 0) : Image(x, y, z, width, height, defaultTextureID) {
        textureIDs["over"] = (mouseOverTextureID) ? mouseOverTextureID : defaultTextureID;
        onClick = nullptr;
    }


    /// Réception de notification d'événement SDL.
    /// \param sdlEvent Événement SDL.
    void notify(SDL_Event *sdlEvent) {
        if ((sdlEvent->button.x >= vertices[0]) && (sdlEvent->button.x <= vertices[3]) &&
            (sdlEvent->button.y >= vertices[1]) && (sdlEvent->button.y <= vertices[4])) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick)
                        onClick();
                    break;

                case SDL_MOUSEMOTION:
                    textureToDraw = textureIDs["over"];
                    break;
            }
        } else
            textureToDraw = textureIDs["default"];
    }

    void updateButtonPosition(double x, double y, double z){
        Matrix m;
        m.loadTranslation(Vector(x, y,z));
        transform(m);

    }
};

#endif
