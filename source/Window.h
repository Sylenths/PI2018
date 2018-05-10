/// \brief Représentation de la fenêtre.
/// \details Affichage de la fenêtre.
/// \author Antoine Legault, Samuel Labelle et Patrick Singcaster
/// \date 27 mars 2018
/// \version 0.1

#ifndef WINDOW_H
#define WINDOW_H

#include "includes.h"

class Window {
protected:
    SDL_Window* sdlWindow;  ///< Fenêtre
    int width; ///< Largeur
    int height; ///< Hauteur

public:
	/// Constructeur.
	/// \param title Titre de la fenètre.
	/// \param x Position en x du coin droit en haut de la fenètre sur l'écran.
	/// \param y Position en y du coin droit en haut de la fenètre sur l'écran.
	/// \param width Largeur de la fenètre, en pixels.
	/// \param height Hauteur de la fenètre, en pixels.
	/// \param flags Flags SDL.
    Window(const char* title, const int& x, const int& y, const int& width, const int& height, const unsigned int& windowflags){
        sdlWindow = SDL_CreateWindow(title, x, y, width, height, windowflags);
        this->width = width;
        this->height = height;
    }

    virtual ~Window() {
       SDL_DestroyWindow(sdlWindow);
    }

    /// Méthode virtuelle pour effacer le contenu de la fenêtre.
    virtual void clear() = 0;
    /// Méthode virtuelle pour rafraîchir le contenu de la fenêtre.
    virtual void refresh()= 0;

};

#endif //SDLPROJECT_WINDOW_H
