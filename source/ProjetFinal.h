/// \brief Représentation du cadre du jeu.
/// \details Le coeur du projet, l'application.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li
/// \date 24 mars 2018, 25 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_PROJETFINAL_H
#define SOURCE_PROJETFINAL_H

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Singleton.h"
#include "ResourceManager.h"
#include "GLContext.h"
#include "Menu.h"
#include "Observable.h"

class ProjetFinal : public Singleton<ProjetFinal> {
private:
    ResourceManager* resourceManager; ///< Composante  ressource Manager qui va nous permettre de gérer nos ressources.
    GLContext* glContext; ///< Composante glContext
    std::list<Menu>* menuList; ///< Composante List de menu
    SDL_Event* sdlEvent;

    std::map<std::string, Observable<SDL_Event*>*> observables; ///< Composante des cartes d'observable

    std::string defaultPath;

public:

    ProjetFinal(const char* title = "P.I. 2018", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 1280, int height = 720, unsigned int windowflags = 0){
        resourceManager = new ResourceManager();
        glContext = new GLContext(title,x ,y ,width , height, windowflags);
        menuList = new std::list<Menu>;
        glContext->setFrustum(90.0, 0.1, 1000.0, false);

        sdlEvent = new SDL_Event();
    }

    ~ ProjetFinal () {
        delete (glContext);
        delete (menuList);
        delete (resourceManager);
        delete (sdlEvent);
    }
    /// Représente la boucle de jeu
    void run(){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /*
         * déplacement de la souris
        sdlEvent.motion.xrel;

         */

        //TODO ajout d'observables
        observables["onMouseClick"] = new Observable<SDL_Event*>();

        //TODO ajout d'objet à afficher

        //resourceManager->addResource("bouton", new );


        bool isOpen = true;
        while (isOpen){
            while(SDL_PollEvent(sdlEvent)) {
                switch (sdlEvent->type) {
                    case SDL_QUIT:
                        isOpen = false;
                        break;
                }
            }
            glContext->clear();
            glContext->refresh();
         }

    }
    void setDefaultPath(std::string defaultPath) {
        this -> defaultPath = defaultPath;
    }


};


#endif
