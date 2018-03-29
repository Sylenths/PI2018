/// \brief Représentation du contexte de la fenêtre.
/// \details Fenêtre contenant un contexte de rendu OpenGL capable d'affichage 2D et 3D.
/// \author Antoine Legault, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.2
/// \warning La position à laquelle la souris est retournée dans resetMousePos() est hardcodée.
/// \bug Aucun connus.
#ifndef SDLPROJECT_GLCONTEXT_H
#define SDLPROJECT_GLCONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cmath>

#include "Window.h"
#include "Matrix.h"

class GLContext : public Window{
private:
    SDL_GLContext glContext; ///< Contexte OpenGL-SDL
public:
	/// Constructeur
	/// \param title Titre de la fenêtre.
	/// \param x Position en x du coin droit en haut de la fenêtre, par rapport à l'écran.
	/// \param y Position en y du coin droit en haut de la fenêtre, par rapport à l'écran.
	/// \param width Largeur de la fenêtre, en pixels.
	/// \param height Hauteur de la fenêtre, en pixels.
	/// \param flags Flags SDL.
    GLContext(const char* title, int x, int y, int width, int height, unsigned int windowflags = 0) : Window(title, x,y,width, height, windowflags | SDL_WINDOW_OPENGL) {
        glContext = SDL_GL_CreateContext(sdlwindow);
    }
	/// Destructeur.
    ~GLContext() {
        SDL_GL_DeleteContext(glContext);
    }

    /// Effacer le contenu de la fenêtre.
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

	/// Prends le contrôle de la souris et du clavier.
	void grabInput(){
		SDL_SetWindowGrab(sdlwindow, SDL_TRUE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	/// Rends le contrôle de la souris et du clavier.
	void releaseInput(){
		SDL_SetWindowGrab(sdlwindow, SDL_FALSE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}

    /// Rafraîchir le contenu de la fenêtre.
    void refresh() {
        SDL_GL_SwapWindow(sdlwindow);
    }
    /// Affichage de l'environnement graphique.
    /// \param angle Angle du champ de vision.
    /// \param nearPlane Distance de la zone de vue rapproché.
    /// \param farPlane Distance de la zone de vue éloignée.
    /// \param is2D Permet de savoir si l'objet est en 2D ou 3D.
    void setFrustum(double angle, double nearPlane, double farPlane, bool is2D) {
        int width, height;
        SDL_GetWindowSize(sdlwindow, &width, &height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(is2D) {
            glOrtho(0.0, (double) width, (double) height, 0.0, 1.0, -1.0);
        }

        else {
            double right = std::tan(angle / 2.0) * nearPlane;
            double top = ((double) height / (double) width) * right;

            Matrix projectionMatrix;
            projectionMatrix.loadProjection(right, top, nearPlane, farPlane);
            glMultMatrixd(projectionMatrix.matrix);

        }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    }
    /// Replacer le curseur de la souris au centre de la fenêtre.
    void resetMousePosition() {
        SDL_WarpMouseInWindow(sdlwindow, 640, 360);
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    }

};


#endif //SDLPROJECT_GLCONTEXT_H
