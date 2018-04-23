/// \brief Représentation du cadre du jeu.
/// \details Le coeur du projet, l'application.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning Le premier compte de FPS sera faussé, car on doit laisser au moins faire un tour de boucle pour savoir sa vraie vitesse de bouclage.
/// \bug Aucuns.
#ifndef PROJETFINAL_H
#define PROJETFINAL_H

#include "includes.h"
#include "Controller.h"

#define IN2D 1
#define IN3D 0
class ProjetFinal : public Singleton<ProjetFinal> {
private:
    GLContext* glContext; ///< GlContext qui va s'occuper de la l'affichage.
    std::map<std::string, Scene*> sceneMap; ///< Carte de menu
    SDL_Event* sdlEvent; ///< Gestionnaire d'évennements
    Scene* sceneDisplay;

    std::map<unsigned int, Observable<SDL_Event*>*> observables; ///< Cartes d'observable pour intéragir avec l'interface.
    Controller* controller;
    bool activeCamera;

    Chrono chrono;
	Chrono FPSchrono;

    unsigned int fps;
    unsigned int timeElapsed;

public:

    /// Chargeur de texture (les mets automatiquement dans le ressource manager).
    /// \param filename Fichier de texture a charger.
    /// \param textureName Nom significatif a donner a la texture.
    static void getTextureID(const char* filename, std::string textureName) {
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

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
              glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
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
        getTextureID("../../images/Delete.png", "deletewindow");
        getTextureID("../../images/SideMenuStructure.png", "StructureWindow");
        getTextureID("../../images/ChoixNonAppuyer.png", "ChoixNonAppuyer");
        getTextureID("../../images/ChoixAppuyer.png", "ChoixAppuyer");
        getTextureID("../../images/SideMenuMachine.png","MachineWindow");
        getTextureID("../../images/SideMenuInformation.png","InformationWindow");
        getTextureID("../../images/SideMenuCable.png","CableWindow");

        //Textures world
        getTextureID("../../images/skysphere_day.png", "daysky");
        getTextureID("../../images/skysphere_night.png", "nightsky");
        getTextureID("../../images/grass.png", "grass");

        getTextureID("../../images/trees/bambou.png", "bambou");
        getTextureID("../../images/trees/cerisier.png", "cerisier");
        getTextureID("../../images/trees/fraksinus.png", "fraksinus");
        getTextureID("../../images/trees/gongko.png", "gongko");
        getTextureID("../../images/trees/mapple.png", "mapple");
        getTextureID("../../images/trees/oak.png", "oak");
        getTextureID("../../images/trees/pin.png", "pin");
        getTextureID("../../images/trees/sequoia.png", "sequoia");

        getTextureID("../../images/fondation.png", "fondation");
        getTextureID("../../images/wall.png", "wall");
        getTextureID("../../images/human.png","human");
        getTextureID("../../images/clouds.png", "clouds");
        getTextureID("../../images/simcoinminer.png", "simcoinminer");

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
        glContext = new GLContext(title, x, y, width, height, 89.0, 0.1, 1000.0, windowflags);
        GLContext::setFrustum(true);
        sdlEvent = new SDL_Event();
        loadTextures();
        controller = new Controller;
        controller->subscribeAll(observables, controller);
        activeCamera = false;
        fps = 0;
    }

    /// Destructeur
    ~ProjetFinal() {
        for (auto it : sceneMap)
            delete it.second;

        delete (glContext);
        delete (sdlEvent);
        delete (controller);
    }

    /// Change la visibilité du nombre d'images par seconde
    void showFPS() {
        ++fps;
        glContext->setFrustum(IS2D);
        double temp = FPSchrono.getElapsed(MICROSECONDS);
        if (FPSchrono.getElapsed(MICROSECONDS) > 1000000.0) { /// le chrono se remet à zéro dans la bouche run()
            char buffer[10];
            SDL_itoa(fps, buffer, 10);
            SDL_SetWindowTitle(glContext->getWindow(), buffer);
            fps = 0;
            FPSchrono.restart();
        }
    }

    /// Représente la boucle de jeu.
    void run(std::string filePath) {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.4);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glCullFace(GL_FRONT_AND_BACK);

        glEnable(GL_POINT_SMOOTH);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        float ambiantLight[] = { 0.9, 0.9, 0.9 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambiantLight);

        SDL_GL_SetSwapInterval(0);

        sceneMap["MainMenu"] = new MainMenu();
        sceneMap["MainMenu"]->subscribeAll(observables);
        sceneDisplay = sceneMap[Scene::getActiveScene()];

        sceneMap["SettingsMenu"] = new SettingsMenu();
        sceneMap["HighScoresMenu"] = new HighScoresMenu();
        sceneMap["PauseMenu"] = new PauseMenu();
        sceneMap["World"] = new World(0, 0, 0, 20, {0, 0, 0});

        chrono.restart();
        while (Scene::getActiveScene() != "Quit") {
            while (SDL_PollEvent(sdlEvent)) {
                switch (sdlEvent->type) {
                    default:
                        if (!observables[sdlEvent->type])
                            observables[sdlEvent->type] = new Observable<SDL_Event *>();
                        observables[sdlEvent->type]->notify(sdlEvent);
                }
            }

            if ((Scene::getActiveScene() != "Quit") && (sceneDisplay != sceneMap[Scene::getActiveScene()])) {
                sceneDisplay->unsubscribeAll(observables);
                sceneDisplay = sceneMap[Scene::getActiveScene()];
                sceneDisplay->subscribeAll(observables);
                controller->subscribeAll(observables, controller);
            }
            addFondation();
            createWall();


            ///controle des touches
            switch (controller->getKeyDown()) {
                case SDLK_f:
                    activeCamera = false;
                    glContext->releaseInput();
                    break;
                case SDLK_g:
                    activeCamera = true;
                    glContext->grabInput();
                    break;
                case SDLK_w:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->startMove(CAMERA_MOVE_FRONT);
                    }
                    break;
                case SDLK_s:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->startMove(CAMERA_MOVE_BACK);
                    }
                    break;
                case SDLK_a:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->startMove(CAMERA_MOVE_LEFT);
                    }
                    break;
                case SDLK_d:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->startMove(CAMERA_MOVE_RIGHT);
                    }
                    break;
                case SDLK_9:
                    ((World*)sceneDisplay)->test = 2;
                    break;
                case SDLK_ESCAPE:
                    if (sceneDisplay == sceneMap["World"]) {
                        glContext->releaseInput();
                        activeCamera = false;
                        sceneDisplay->changeActiveScene("PauseMenu");
                    }
                    break;
            }
            switch (controller->getKeyUp()) {
                case SDLK_w:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->stopMove(CAMERA_MOVE_FRONT);
                    }
                    break;
                case SDLK_s:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->stopMove(CAMERA_MOVE_BACK);
                    }
                    break;
                case SDLK_a:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->stopMove(CAMERA_MOVE_LEFT);
                    }
                    break;
                case SDLK_d:
                    if (sceneDisplay == sceneMap["World"]) {
                        sceneDisplay->getCamera()->stopMove(CAMERA_MOVE_RIGHT);
                    }
                    break;
            }
            ///controle de la rotation de la camera
            if (activeCamera) {
                sceneDisplay->getCamera()->rotateView(controller->getMouseMotion()[0], controller->getMouseMotion()[1]);
                controller->resetMouseMotion();
            }

                if (sceneDisplay != sceneMap[Scene::getActiveScene()] && Scene::getActiveScene() != "Quit") {
                    sceneDisplay->unsubscribeAll(observables);
                    sceneDisplay = sceneMap[Scene::getActiveScene()];
                    sceneDisplay->subscribeAll(observables);

                }
            if (sceneDisplay == sceneMap["World"] && activeCamera)
                    sceneDisplay->getCamera()->update(chrono.getElapsed(SECONDS));

            glContext->clear();

            sceneDisplay->draw();
            if(Scene::getActiveFPS() == true)
                showFPS();
            else
                SDL_SetWindowTitle(glContext->getWindow(), "P.I. 2018");
            glContext->refresh();
	        chrono.restart();

            controller->resetClicMousePosition();

        }
    }

    void addFondation(){
        if(activeCamera && Scene::getActiveScene() == "World" && controller->getClickMousePosition()[2] == SDL_BUTTON_LEFT){
            World* world = ((World*)sceneDisplay);




            if(world->hud->isConstructingFondation) {

                Vector front = world->getCamera()->getFront();
                Vector pos = world->getCamera()->getPos();
                Vector nFloor = {0.0, 2.5, 0.0};
                if (front * nFloor) {
                    double ratio = -(pos.y / front.y);
                    if (ratio > 0) {
                        Vector intersection = (front * ratio) + pos;
                        int x = round(intersection.x / 2.0);
                        int z = round(intersection.z / 2.0);
                        std::map<std::pair<int,int>, Fondation*>* fondationGrid = world->hud->getFondations();
                        if(!(*fondationGrid)[std::make_pair(x,z)]) {
                            Fondation* fondation = new Fondation((double)x * 2.0, 0.0, (double)z * 2.0, false);
                            if ((*fondationGrid)[std::make_pair(x - 1, z)]){
                                if(!(*fondationGrid)[std::make_pair(x,z)])
                                    (*fondationGrid)[std::make_pair(x,z)] = fondation;
                                (*fondationGrid)[std::make_pair(x,z)]->west = (*fondationGrid)[std::make_pair(x - 1, z)];
                                (*fondationGrid)[std::make_pair(x - 1, z)]->east = (*fondationGrid)[std::make_pair(x,z)];
                            }

                            if((*fondationGrid)[std::make_pair(x + 1, z)]){
                                if(!(*fondationGrid)[std::make_pair(x,z)])
                                    (*fondationGrid)[std::make_pair(x,z)] = fondation;
                                (*fondationGrid)[std::make_pair(x,z)]->east = (*fondationGrid)[std::make_pair(x + 1, z)];
                                (*fondationGrid)[std::make_pair(x + 1, z)]->west = (*fondationGrid)[std::make_pair(x,z)];
                            }

                            if((*fondationGrid)[std::make_pair(x, z - 1)]){
                                if(!(*fondationGrid)[std::make_pair(x,z)])
                                    (*fondationGrid)[std::make_pair(x,z)] = fondation;
                                (*fondationGrid)[std::make_pair(x,z)]->north = (*fondationGrid)[std::make_pair(x , z - 1)];
                                (*fondationGrid)[std::make_pair(x , z - 1)]->south = (*fondationGrid)[std::make_pair(x,z)];
                            }

                            if((*fondationGrid)[std::make_pair(x, z + 1)]){
                                if(!(*fondationGrid)[std::make_pair(x,z)])
                                    (*fondationGrid)[std::make_pair(x,z)] = fondation;
                                (*fondationGrid)[std::make_pair(x,z)]->south = (*fondationGrid)[std::make_pair(x , z + 1)];
                                (*fondationGrid)[std::make_pair(x , z + 1)]->north = (*fondationGrid)[std::make_pair(x,z)];
                            }

                            if((*fondationGrid)[std::make_pair(x,z)])
                                world->addModel((*fondationGrid)[std::make_pair(x,z)]);
                        }
                    }
                }




            }

        }
    }

    void createWall(){
        if (((World *) sceneDisplay)->test == 2) {
            ((World *) sceneDisplay)->test = 0;
            std::map<std::pair<int, int>, Fondation *> *fondationGrid = ((World *) sceneDisplay)->hud->getFondations();
            Fondation *start = /*((BuildWall *) ((World*)sceneDisplay)->hud->getActions()->front())->getFondation()*/ (*fondationGrid)[std::make_pair(
                    0, 0)];
            while (start->north) {
                start = start->north;
            }
            Fondation *previousPosition = start;
            Fondation *currentPosition;
            Fondation *switchVariable;
            std::list<Vector> corner;

            if (previousPosition->east) {
                currentPosition = previousPosition->east;
                if(previousPosition->west){
                    corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                }
                if(previousPosition->south){
                    corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                }
            } else {
                corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                if (previousPosition->south) {
                    currentPosition = previousPosition->south;
                } else {
                    corner.push_front((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                    if (previousPosition->west) {
                        currentPosition = previousPosition->west;
                    } else {
                        currentPosition = previousPosition;
                        corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                        corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                    }
                }
            }

            while (!((start->centerPoint->x == currentPosition->centerPoint->x) &&
                     (start->centerPoint->z == currentPosition->centerPoint->z))) {


                ///deplace vers l'est et regarde a le nord
                if (currentPosition == previousPosition->east) {
                    if (!currentPosition->north) {
                        if (currentPosition->east) {
                            previousPosition = currentPosition;
                            currentPosition = currentPosition->east;
                        } else {
                            if (currentPosition->south) {
                                previousPosition = currentPosition;
                                currentPosition = currentPosition->south;
                                corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                            } else {
                                previousPosition = currentPosition;
                                currentPosition = currentPosition->west;
                                corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                                corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                            }
                        }
                    } else {
                        previousPosition = currentPosition;
                        currentPosition = currentPosition->north;
                        corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                    }

                }
                else {
                    ///deplace vers le sud et regarde a l'est
                    if (currentPosition == previousPosition->south) {
                        if (!currentPosition->east) {
                            if (currentPosition->south) {
                                previousPosition = currentPosition;
                                currentPosition = currentPosition->south;
                            } else {
                                if (currentPosition->west) {
                                    previousPosition = currentPosition;
                                    currentPosition = currentPosition->west;
                                    /* +1,+1*/                            corner.push_back(
                                            (*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                                } else {
                                    previousPosition = currentPosition;
                                    currentPosition = currentPosition->north;
                                    corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                                    corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                                }
                            }
                        } else {
                            previousPosition = currentPosition;
                            currentPosition = currentPosition->east;
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                        }

                    } else {
                        ///deplace vers l'oest et regarde a le sud
                        if (currentPosition == previousPosition->west) {

                            if (!currentPosition->south) {
                                if (currentPosition->west) {
                                    previousPosition = currentPosition;
                                    currentPosition = currentPosition->west;
                                } else {
                                    if (currentPosition->north) {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->north;
                                        /*-1+1*/                                   corner.push_back(
                                                (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                                    } else {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->east;
                                        corner.push_back(
                                                (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                                        corner.push_back(
                                                (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                                    }
                                }
                            } else {
                                previousPosition = currentPosition;
                                currentPosition = currentPosition->south;
                                corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                            }

                        } else {
                            ///deplace vers le nord et regarde a l'oest
                            if (currentPosition == previousPosition->north) {
                                if (!currentPosition->west) {
                                    if (currentPosition->north) {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->north;
                                    } else {
                                        if (currentPosition->east) {
                                            previousPosition = currentPosition;
                                            currentPosition = currentPosition->east;
                                            /*-1-1*/                              corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                                        } else {
                                            previousPosition = currentPosition;
                                            currentPosition = currentPosition->south;
                                            corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                                            corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                                        }
                                    }
                                } else {
                                    previousPosition = currentPosition;
                                    currentPosition = currentPosition->west;
                                    corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                                }
                            }
                        }

                    }
                }





            }
            int size = corner.size() - 1;
            Vector first = corner.front();
            for (int i = 0; i < size; ++i) {
                Vector temp = corner.front();
                corner.pop_front();
                ((World *) sceneDisplay)->addModel(
                        new Model(/*((BuildWall *) hud->getActions()->front())->getHeight()*/
                                3.0, /*((BuildWall *) hud->getActions()->front())->getMateriel()->getTextureID()*/
                                ResourceManager::getInstance()->getTexture("wall"), &temp, &corner.front()));
            }
            ((World *) sceneDisplay)->addModel(new Model(/*((BuildWall *) hud->getActions()->front())->getHeight()*/
                    3.0, /*((BuildWall *) hud->getActions()->front())->getMateriel()->getTextureID()*/
                    ResourceManager::getInstance()->getTexture("wall"), &corner.front(), &first));

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
