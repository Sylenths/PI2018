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

    /// Charge toutes les textures necessaire au programme
    void loadTextures() {
        //Textures boutons menu principal
        getTextureID("../../images/start.png", "ButtonStart");
        getTextureID("../../images/starto.png", "ButtonStartOver");
        getTextureID("../../images/settings.png", "ButtonSettings");
        getTextureID("../../images/settingso.png", "ButtonSettingsOver");
        getTextureID("../../images/highscore.png", "ButtonHighScore");
        getTextureID("../../images/highscoreo.png", "ButtonHighScoreOver");
        getTextureID("../../images/maisonApp.png", "FondMaison");
        getTextureID("../../images/grass.png", "grass");
        getTextureID("../../images/cielnuageu.png", "sky");

     //Texture pour le InGameOverlay
        getTextureID("../../images/alert_ico.png", "alert");
        getTextureID("../../images/delete_btn.png", "delete");
        getTextureID("../../images/info_btn.png", "info");
        getTextureID("../../images/Machines_btn.png", "machine");
        getTextureID("../../images/skipturn_btn.png", "skipTurn");
        getTextureID("../../images/struct_btn.png", "structure");
        getTextureID("../../images/topbar_tex.png", "topBar");
        getTextureID("../../images/wire_btn.png", "wire");
        
        //Textures boutons settings
        getTextureID("../../images/BoutonNO.png", "FPSButton");
        getTextureID("../../images/BoutonNO.png", "FPSButtonNO");
        getTextureID("../../images/BoutonYES.png", "FPSButtonYES");
        getTextureID("../../images/BoutonBack.png", "backButton");
        getTextureID("../../images/SettingsMenu.png", "FondSettings");
        getTextureID("../../images/backOver.png", "BackButtonOver");
        getTextureID("../../images/BoutonYESOver.png", "FPSButtonYESOver");
        getTextureID("../../images/BoutonNOOver.png", "FPSButtonNOOVER");
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

        sceneMap["MainMenu"] = new MainMenu();
        sceneMap["MainMenu"]->subscribeAll(&observables);
        sceneDisplay = sceneMap[Scene::getActiveScene()];

        sceneMap["Settings"] = new Settings();
        sceneMap["InGameESC"] = new InGameESC();
        sceneMap["Highscore"] = new Highscore();
        sceneMap["World"] = new World();
    }

    /// Destructeur
    ~ProjetFinal () {
        delete (glContext);
        delete (sdlEvent);
        for (auto it : sceneMap) {
            delete (it.second);
        }
    }

    /// Permet de changer le mode d'affichage du projet entre 2D et 3D.
    /// \param is2D Booléen représentant si c'est en 2D (true), ou en 3D (false).
 //   void setFrustum(bool is2D) {
   //     glContext->setFrustum(90.0, 0.1, 1000.0, is2D);
  //  }

    /// Représente la boucle de jeu.
    void run(std::string filePath){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /*
         * déplacement de la souris
        sdlEvent.motion.xrel;

         */

        //TODO ajout d'objet à afficher

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

            if (sceneDisplay != sceneMap[Scene::getActiveScene()]) {
              sceneDisplay->unsubscribeAll(&observables);
              sceneDisplay = sceneMap[Scene::getActiveScene()];
              sceneDisplay->subscribeAll(&observables);
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
};
#endif
