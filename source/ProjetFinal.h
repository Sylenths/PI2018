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
    GLContext* glContext; ///< GlContext qui va s'occuper de la l'affichage.
    std::list<Menu>* menuList; ///< Liste de menu
    SDL_Event* sdlEvent;

    std::map<unsigned int, Observable<SDL_Event*>*> observables; ///< Cartes d'observable pour intéragir avec l'interface.

    std::string defaultPath;

public:

    ProjetFinal(const char* title = "P.I. 2018", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 1280, int height = 720, unsigned int windowflags = 0){
        glContext = new GLContext(title,x ,y ,width , height, windowflags);
        menuList = new std::list<Menu>;
        glContext->setFrustum(90.0, 0.1, 1000.0, false);

        sdlEvent = new SDL_Event();
    }

    ~ProjetFinal () {
        delete (glContext);
        delete (menuList);
        delete (sdlEvent);
    }
    /// Représente la boucle de jeu

    void getTextureID(const char* filename, std::string textureName){
            unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            SDL_Surface* surface = IMG_Load(filename);
            glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
            SDL_FreeSurface(surface);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            ResourceManager::getInstance()->addTexture(textureName, textureID);
    }

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

        //TODO ajout d'objet à afficher

        //resourceManager->addResource("bouton", new );


        bool isOpen = true;
        while (isOpen){
            while(SDL_PollEvent(sdlEvent)) {
                switch (sdlEvent->type) {
                    case SDL_QUIT:
                        isOpen = false;
                        break;

                    default:
                        if(!observables[sdlEvent->type])
                            observables[sdlEvent->type] = new Observable<SDL_Event*>;
                        observables[sdlEvent->type]->notify(sdlEvent);

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
