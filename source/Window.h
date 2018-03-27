/// \brief Représentation de la fenêtre.
/// \details Affichage de la fenêtre.
/// \author Antoine Legault, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.
#ifndef SDLPROJECT_WINDOW_H
#define SDLPROJECT_WINDOW_H
#include <SDL2/SDL.h>

class Window {
protected:
    SDL_Window* sdlwindow;  ///< Affichage de la fenêtres.

public:

	/// Constructeur.
	/// \param title Titre de la fenètre.
	/// \param x Position en x du coin droit en haut de la fenètre sur l'écran.
	/// \param y Position en y du coin droit en haut de la fenètre sur l'écran.
	/// \param width Largeur de la fenètre, en pixels.
	/// \param height Hauteur de la fenètre, en pixels.
	/// \param flags Flags SDL.
    Window(const char* title, int x, int y, int width, int height, unsigned int windowflags){
        sdlwindow = SDL_CreateWindow(title, x, y, width, height, windowflags);
    }

    virtual ~Window(){
       SDL_DestroyWindow(sdlwindow);
    }
    /// Méthode virtuelle pour effacer le contenu de la fenêtre.
    virtual void clear() = 0;
    /// Méthode virtuelle pour rafraîchir le contenu de la fenêtre.
    virtual void refresh()= 0;

};


#endif //SDLPROJECT_WINDOW_H
