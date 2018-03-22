/// \brief Représentation de la fenêtre.
/// \details Affichage de la fenêtre.
/// \author Antoine Legault
/// \date 20 février 2018
/// \version 0.1
/// \warning Risque de planter si mal utilisé.
/// \bug aucun bug
#ifndef SDLPROJECT_WINDOW_H
#define SDLPROJECT_WINDOW_H
#include <SDL2/SDL.h>

class Window {
protected:
    SDL_Window *sdlwindow;  ///< Composante sdlwindow.

public:
    Window(const char* title, int x, int y, int width, int height, unsigned int windowflags){
        sdlwindow = SDL_CreateWindow(title, x, y, width, height, windowflags);
    }

    virtual ~Window(){
       SDL_DestroyWindow(sdlwindow);
    }
    /// Méthode virtuel  pour effacer le contenu de la fenêtre.
    virtual void clear() = 0;
    /// Méthode virtuel  pour rafraichir le contenu de la fenêtre.
    virtual void refresh()= 0;

};


#endif //SDLPROJECT_WINDOW_H
