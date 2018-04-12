/// \brief Représentation du cadre du jeu.
/// \details Le coeur du projet, l'application.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.
#ifndef PROJETFINAL_H
#define PROJETFINAL_H

#include "includes.h"

#define IN2D 1
#define IN3D 0
class ProjetFinal : public Singleton<ProjetFinal> {
private:
    GLContext* glContext; ///< GlContext qui va s'occuper de la l'affichage.
    std::map<std::string, Scene*> sceneMap; ///< Carte de menu
    SDL_Event* sdlEvent; ///< Gestionnaire d'évennements
    Scene* sceneDisplay;

    std::map<unsigned int, Observable<SDL_Event*>*> observables; ///< Cartes d'observable pour intéragir avec l'interface.

public:

    /// Change la visibilité du nombre d'images par seconde
    void setShowFPS(){

    }

    /// Chargeur de texture (les mets automatiquement dans le ressource manager).
    /// \param filename Fichier de texture a charger.
    /// \param textureName Nom significatif a donner a la texture.
    static void getTextureID(const char* filename, std::string textureName){
            unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            SDL_Surface* surface = IMG_Load(filename);
            #if defined(_WIN32) || defined(__linux__)
              glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	    #else
              glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	    #endif
            SDL_FreeSurface(surface);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            ResourceManager::getInstance()->addTexture(textureName, textureID);
    }

    /// Charge toutes les textures necessaire au programme
    void loadTextures() {
        //Texture pour le InGameOverlay
        getTextureID("../../images/alert_ico.png", "alert");
        getTextureID("../../images/delete_btn.png", "delete");
        getTextureID("../../images/info_btn.png", "info");
        getTextureID("../../images/Machines_btn.png", "machine");
        getTextureID("../../images/skipturn_btn.png", "skipTurn");
        getTextureID("../../images/struct_btn.png", "structure");
        getTextureID("../../images/topbar_tex.png", "topBar");
        getTextureID("../../images/wire_btn.png", "wire");

        //Textures world
        getTextureID("../../images/grass.png", "grass");
        getTextureID("../../images/daysky.png", "sky");
        getTextureID("../../images/fan.png", "fan");

        //Textures boutons menu principal
        getTextureID("../../images/start.png", "ButtonStart");
        getTextureID("../../images/starto.png", "ButtonStartOver");
        getTextureID("../../images/settings.png", "ButtonSettings");
        getTextureID("../../images/settingso.png", "ButtonSettingsOver");
        getTextureID("../../images/highscore.png", "ButtonHighScore");
        getTextureID("../../images/highscoreo.png", "ButtonHighScoreOver");
        getTextureID("../../images/QuitGame.png", "ButtonQuitGame");
        getTextureID("../../images/QuitGameOver.png", "ButtonQuitGameOver");
        getTextureID("../../images/maisonApp.png", "FondMaison");

        //Textures boutons settings
        getTextureID("../../images/BoutonNO.png", "FPSButton");
        getTextureID("../../images/BoutonNO.png", "FPSButtonNO");
        getTextureID("../../images/BoutonYES.png", "FPSButtonYES");
        getTextureID("../../images/BoutonBack.png", "backButton");
        getTextureID("../../images/SettingsMenu.png", "FondSettings");
        getTextureID("../../images/backOver.png", "BackButtonOver");
        getTextureID("../../images/BoutonYESOver.png", "FPSButtonYESOVER");
        getTextureID("../../images/BoutonNOOver.png", "FPSButtonNOOVER");

        //Textures menu Highscore
        getTextureID("../../images/MenuHighScore.png","FondHighscore");

        //Textures Pause Menu
        getTextureID("../../images/PauseQuitGame.png", "PauseQuitGame");
        getTextureID("../../images/PauseQuitGameOver.png", "PauseQuitGameOver");
        getTextureID("../../images/PauseResumeGame.png", "PauseResumeGame");
        getTextureID("../../images/PauseResumeGameOver.png", "PauseResumeGameOver");
        getTextureID("../../images/PauseSettings.png", "PauseSettings");
        getTextureID("../../images/PauseSettingsOver.png", "PauseSettingsOver");
        getTextureID("../../images/PauseMenuFond.png", "PauseMenuFond");
    }

	/// Constructeur
    /// \param title Titre de la fenêtre.
    /// \param x Position en x du coin droit en haut de la fenêtre, par rapport à l'écran.
    /// \param y Position en y du coin droit en haut de la fenêtre, par rapport à l'écran.
    /// \param width Largeur de la fenêtre, en pixels.
    /// \param height Hauteur de la fenêtre, en pixels.
    /// \param windowflags Flags SDL.
    ProjetFinal(const char* title = "P.I. 2018", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 1280, int height = 720, unsigned int windowflags = 0) {
        glContext = new GLContext(title, x, y, width, height,90.0, 0.1, 1000.0, windowflags);
        GLContext::setFrustum( true);
        sdlEvent = new SDL_Event();
        loadTextures();
    }

    /// Destructeur
    ~ProjetFinal () {
        for (auto it : sceneMap)
            delete it.second;

        delete (glContext);
        delete (sdlEvent);
    }

    /// Représente la boucle de jeu.
    void run(std::string filePath){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        sceneMap["MainMenu"] = new MainMenu();
        sceneMap["MainMenu"]->subscribeAll(observables);
        sceneDisplay = sceneMap[Scene::getActiveScene()];

        sceneMap["Settings"] = new Settings();
        sceneMap["InGameESC"] = new InGameESC();
        sceneMap["Highscore"] = new Highscore();
        sceneMap["PauseMenu"] = new PauseMenu();
        sceneMap["World"] = new World(0, 0, 0, 20, {0, 0, 0});

        bool isOpen = true;
        while (isOpen){
            if(Scene::getActiveScene() == "Quit")
                isOpen = false;
            while(SDL_PollEvent(sdlEvent)) {
                switch (sdlEvent->type) {

                    default:
                        if(!observables[sdlEvent->type])
                            observables[sdlEvent->type] = new Observable<SDL_Event*>();
                         observables[sdlEvent->type]->notify(sdlEvent);
                }
            }




            // Test Highscore
            Highscore* test= new Highscore;
            test->updateScore("Jade",8);

            //if(sceneDisplay == sceneMap["World"]) glContext->resetMousePosition();


            if (sceneDisplay != sceneMap[Scene::getActiveScene()]) {
              sceneDisplay->unsubscribeAll(observables);
              sceneDisplay = sceneMap[Scene::getActiveScene()];
              sceneDisplay->subscribeAll(observables);
            }

            glContext->clear();
            sceneDisplay->draw();
            glContext->refresh();
         }
    }

    Vector get2DTextureSize(const char* filePath) {
        SDL_Surface* surface = IMG_Load(filePath);
        Vector size = {(double)surface->w, (double)surface->h, 0};
        SDL_FreeSurface(surface);

        return size;
    }
    GLContext* getGlContext(){
        return glContext;
    }
};
#endif
