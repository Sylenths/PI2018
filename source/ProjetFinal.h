/// \brief Représentation du cadre du jeu.
/// \details Le coeur du projet, l'application.
/// \author Antoine Legault, Jade St-Pierre Bouchard
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_PROJETFINAL_H
#define SOURCE_PROJETFINAL_H

#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "Singleton.h"
#include "ResourceManager.h"
#include "GLContext.h"
#include "Menu.h"
#include "Observable.h"

class ProjetFinal : public Singleton {
public:
    ResourceManager* ressourceManagerList; ///< Composante Liste de ressourceManager
    GLContext* glContext; ///< Composante Liste de ressourceManager
    std::list<Menu>* menuList; ///< Composante
    //GLContext glContext("SDL - OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, 0);


    ProjetFinal(const char* title, int x, int y, int width, int height, unsigned int windowflags = 0){
        ressourceManagerList = new ResourceManager();
        glContext = new GLContext(title,x ,y ,width , height, windowflags);
        menuList = new std::list<Menu>;
    }

    ProjetFinal~(){
        delete (glContext);
        delete (menuList);
        delete (ressourceManagerList);
    }

    void run(){

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        SDL_ShowCursor(SDL_DISABLE);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        SDL_Event sdlEvent;
        /*
         * déplacement de la souris
        sdlEvent.motion.xrel;

         */
        bool isOpen = true;
        while (isOpen){
            while(SDL_PollEvent(&sdlEvent)) {
                switch (sdlEvent.type) {
                    case SDL_QUIT:
                        isOpen = false;
                        break;
                }
            }
            glContext->clear();
            glContext->refresh();
    }



};


#endif
