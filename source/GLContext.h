/// \brief Représentation du contexte de la fenêtre.
/// \details Forme et grandeur de la fenêtre affiché.
/// \author Antoine Legault
/// \date 20 février 2018
/// \version 0.1
/// \warning Risque de planter si mal utilisé.
/// \bug aucun bug
#ifndef SDLPROJECT_GLCONTEXT_H
#define SDLPROJECT_GLCONTEXT_H

#include <SDL2/SDL.h>
#include "Window.h"
#include <SDL2/SDL_opengl.h>
#include <cmath>
#include "Matric.h"

class GLContext : public Window{
private:
    SDL_GLContext glContext;    ///< Composante glContext.
public:
    GLContext(const char* title, int x, int y, int width, int height, unsigned int windowflags = 0) : Window(title, x,y,width, height, windowflags | SDL_WINDOW_OPENGL){
        glContext = SDL_GL_CreateContext(sdlwindow);
    }

    ~GLContext(){
        SDL_GL_DeleteContext(glContext);
    }

    /// Vider le contenu de la fenêtre.
    void clear(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// Rafraichir le contenu de la fenêtre.
    void refresh(){
        SDL_GL_SwapWindow(sdlwindow);
    }
    /// Affichage de l'environnement graphique.
    /// \param angle L'inclinaison de l'angle.
    /// \param nearPlane Distance de la zone de vue rapproché.
    /// \param farPlane Distance de la zone de vue éloignée.
    /// \param is2D Permet de savoir si l'objet est en 2D ou 3D.
    void setFrustum(double angle, double nearPlane, double farPlane, bool is2D){
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

            Matric projectionMatrix;
            projectionMatrix.loadProjection(right, top, nearPlane, farPlane);
            glMultMatrixd(projectionMatrix.matrix);

        }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    }
    /// Replacer le curseur de la souris au centre de la fenêtre.
    void RessetMousePosition(){
        SDL_WarpMouseInWindow(sdlwindow, 500, 350);
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    }

};


#endif //SDLPROJECT_GLCONTEXT_H
