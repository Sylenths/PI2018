/// \brief Représentation du cadre du jeu.
/// \details Le coeur du projet, l'application.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.
#ifndef PROJETFINAL_H
#define PROJETFINAL_H

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
#include "MainMenu.h"
#include "Settings.h"
#include "InGameOverlay.h"
#include "InGameESC.h"
#include "Highscore.h"
#include "Image2D.h"
#include "Vector3D.h"

#include "onClickFunctionsPart1.h"
#include "Button.h"

class ProjetFinal : public Singleton<ProjetFinal> {
private:
    GLContext* glContext; ///< GlContext qui va s'occuper de la l'affichage.
    std::map<std::string, Menu*> menuMap; ///< Carte de menu
    Menu* menuDisplay;
    SDL_Event* sdlEvent; ///< Gestionnaire d'évennements

    std::map<unsigned int, Observable<SDL_Event*>*> observables; ///< Cartes d'observable pour intéragir avec l'interface.

public:

	/// Constructeur
    /// \param title Titre de la fenêtre.
    /// \param x Position en x du coin droit en haut de la fenêtre, par rapport à l'écran.
    /// \param y Position en y du coin droit en haut de la fenêtre, par rapport à l'écran.
    /// \param width Largeur de la fenêtre, en pixels.
    /// \param height Hauteur de la fenêtre, en pixels.
    /// \param windowflags Flags SDL.
    ProjetFinal(const char* title = "P.I. 2018", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 1280, int height = 720, unsigned int windowflags = 0){
        glContext = new GLContext(title,x ,y ,width , height, windowflags);
        glContext->setFrustum(90.0, 0.1, 1000.0, true);
        sdlEvent = new SDL_Event();

        menuMap["MainMenu"] = new MainMenu;
        menuMap["Settings"] = new Settings;
        menuMap["InGameOverlay"] = new InGameOverlay;
        menuMap["InGameESC"] = new InGameESC;
        menuMap["Highscore"] = new Highscore;

        menuDisplay = menuMap["MainMenu"];
    }
    /// Destructeur
    ~ProjetFinal () {
        delete (glContext);
        delete (sdlEvent);
        //TODO Delete menuMap.
    }


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

    void loadTextures() {
        getTextureID("images/start.png", "ButtonStart");
        getTextureID("images/settings.png", "ButtonSettings");
        getTextureID("images/highscore.png", "ButtonHighScore");
        getTextureID("images/maisonApp.png", "FondMaison");


    }

    /// Permet de changer le mode d'affichage du projet entre 2D et 3D.
    /// \param is2D Booléen représentant si c'est en 2D (true), ou en 3D (false).
    void setFrustum(bool is2D) {
        glContext->setFrustum(90.0, 0.1, 1000.0, is2D);
    }

    /// Représente la boucle de jeu.

    void run(std::string filePath){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                setFrustum(true);


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /*
         * déplacement de la souris
        sdlEvent.motion.xrel;

         */

        //TODO ajout d'objet à afficher
        loadTextures();

        menuDisplay->loadMenu();

        //resourceManager->addResource("bouton", new );

      /*  getTextureID((filePath + "start.png").c_str(), "start");

        Vector3D dimension = get2DTextureSize((filePath + "start.png").c_str());

        Button* testButton = new Button(testFUNCTION, "start", 100, 100, 1, dimension.x, dimension.y);
        if(!observables[SDL_MOUSEBUTTONDOWN])
            observables[SDL_MOUSEBUTTONDOWN]= new Observable<SDL_Event*>;
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(testButton);

        ResourceManager::getInstance()->addResource("start", testButton);
*/
        bool isOpen = true;
        while (isOpen){
            while(SDL_PollEvent(sdlEvent)) {
                switch (sdlEvent->type) {
                    case SDL_QUIT:
                        isOpen = false;
                        break;

                    default:
                        if(!observables[sdlEvent->type])
                            observables[sdlEvent->type] = new Observable<SDL_Event *>;
                        observables[sdlEvent->type]->notify(sdlEvent);
                }
            }
            glContext->clear();

            menuDisplay->draw();
           // ResourceManager::getInstance()->getResource("start")->draw();

            glContext->refresh();
         }

    }

    Vector3D get2DTextureSize(const char* filePath) {
        SDL_Surface* surface = IMG_Load(filePath);
        Vector3D size = {(double)surface->w, (double)surface->h, 0};
        SDL_FreeSurface(surface);

        return size;
    }

    void test() {
        //std::cout << "Hello World!";
    }



};

#include "onClickFunctionsPart2.h"

#endif
