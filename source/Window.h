/// \brief Représentation de la fenêtre.
/// \details Affichage de la fenêtre.
/// \author Antoine Legault, Samuel Labelle et Patrick Singcaster
/// \date 27 mars 2018
/// \version 0.1

#ifndef SDLPROJECT_WINDOW_H
#define SDLPROJECT_WINDOW_H

#include <SDL2/SDL.h>

class Window {
protected:
    SDL_Window* sdlWindow;  ///< Affichage de la fenêtres.
    static unsigned int width, height;

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
    }

    virtual ~Window() {
       SDL_DestroyWindow(sdlWindow);
    }

    void setSize(const int& width, const int&height) {
        SDL_SetWindowSize(sdlWindow, width, height);
        Window::width = width;
        Window::height = height;
    }

    /// Méthode virtuelle pour effacer le contenu de la fenêtre.
    virtual void clear() = 0;
    /// Méthode virtuelle pour rafraîchir le contenu de la fenêtre.
    virtual void refresh()= 0;

};

unsigned int Window::width;
unsigned int Window::height;

#endif //SDLPROJECT_WINDOW_H
