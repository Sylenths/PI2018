/// \brief Représentation du cadre du jeu.
/// \details Le coeur du projet, l'application.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle, Shelby Versailles
/// \date 3 mai 2018
/// \version 0.1
/// \warning Le premier compte de FPS sera faussé, car on doit laisser au moins faire un tour de boucle pour savoir sa vraie vitesse de bouclage.
/// \bug Aucuns.
#ifndef PROJETFINAL_H
#define PROJETFINAL_H

#include "includes.h"
#include "Controller.h"
#include "Physics.h"

#define IN2D 1
#define IN3D 0
class ProjetFinal : public Singleton<ProjetFinal> {
private:
    GLContext* glContext; ///< GlContext qui va s'occuper de la l'affichage.
    std::map<std::string, Scene*> sceneMap; ///< Carte de menu
    SDL_Event* sdlEvent; ///< Gestionnaire d'évennements
    Scene* sceneDisplay; ///<La scène qui s'affiche présentement

    std::map<unsigned int, Observable<SDL_Event*>*> observables; ///< Cartes d'observable pour intéragir avec l'interface.
    Controller* controller; ///<Gère les entrés utilisateurs
    bool activeCamera; ///<Indique si la caméra est controllée par l'utilisateur

    Chrono chrono; ///<Chrono principale de la boucle de jeu
	Chrono FPSchrono;///<Chrono pour les FPS

    unsigned int fps;///<Les Fps de l'application

public:
    /// Charge toutes les textures necessaire au programme
    void loadTextures() {
        //Texture pour le InGameOverlay
        EntityManager::add(new Texture2d("alert", "../../images/alert_ico.png"));
        EntityManager::add(new Texture2d("delete", "../../images/delete_btn.png"));
        EntityManager::add(new Texture2d("info", "../../images/info_btn.png"));
        EntityManager::add(new Texture2d("machine", "../../images/Machines_btn.png"));
        EntityManager::add(new Texture2d("skipTurn", "../../images/skipturn_btn.png"));
        EntityManager::add(new Texture2d("structure", "../../images/struct_btn.png"));
        EntityManager::add(new Texture2d("topBar", "../../images/topbar_tex.png"));
        EntityManager::add(new Texture2d("wire", "../../images/wire_btn.png"));
        EntityManager::add(new Texture2d("deletewindow", "../../images/Delete.png"));
        EntityManager::add(new Texture2d("StructureWindow", "../../images/SideMenuStructure.png"));
        EntityManager::add(new Texture2d("ChoixNonAppuyer", "../../images/ChoixNonAppuyer.png"));
        EntityManager::add(new Texture2d("ChoixAppuyer", "../../images/ChoixAppuyer.png"));
        EntityManager::add(new Texture2d("MachineWindow", "../../images/SideMenuMachine.png"));
        EntityManager::add(new Texture2d("InformationWindow", "../../images/SideMenuInformation.png"));
        EntityManager::add(new Texture2d("CableWindow", "../../images/SideMenuCable.png"));
        EntityManager::add(new Texture2d("BuildButton", "../../images/BuildButton.png"));
        EntityManager::add(new Texture2d("BuildButtonOver", "../../images/BuildButtonOver.png"));
        EntityManager::add(new Texture2d("CancelButton", "../../images/CancelButton.png"));
        EntityManager::add(new Texture2d("CancelButtonOver", "../../images/CancelButtonOver.png"));
        EntityManager::add(new Texture2d("SimcoinsButtonOver", "../../images/SimCoinMinerButtonO.png"));
        EntityManager::add(new Texture2d("SimcoinsButton", "../../images/SimCoinMinerButton.png"));
        EntityManager::add(new Texture2d("PanneauSolaireButtonOver", "../../images/PanneauSolaireO.png"));
        EntityManager::add(new Texture2d("PanneauSolaireButton", "../../images/PanneauSolaire.png"));
        EntityManager::add(new Texture2d("WindTurbineButtonOver", "../../images/WindTurbineButtonO.png"));
        EntityManager::add(new Texture2d("WindTurbineButton", "../../images/WindTurbineButton.png"));
        EntityManager::add(new Texture2d("UpButton", "../../images/UpButton.png"));
        EntityManager::add(new Texture2d("DownButton", "../../images/DownButton.png"));
        EntityManager::add(new Texture2d("PlusButton", "../../images/BoutonPlus.png"));
        EntityManager::add(new Texture2d("MoinsButton", "../../images/BoutonMoins.png"));

        //Textures world
        EntityManager::add(new Texture2d("meteorite", "../../images/meteorite.png"));
        EntityManager::add(new Texture2d("daysky", "../../images/skysphere_day.png"));
        EntityManager::add(new Texture2d("nightsky", "../../images/skysphere_night.png"));
        EntityManager::add(new Texture2d("grass", "../../images/grass.png"));

        EntityManager::add(new Texture2d("bambou", "../../images/trees/bambou.png"));
        EntityManager::add(new Texture2d("cerisier", "../../images/trees/cerisier.png"));
        EntityManager::add(new Texture2d("fraksinus", "../../images/trees/fraksinus.png"));
        EntityManager::add(new Texture2d("gongko", "../../images/trees/gongko.png"));
        EntityManager::add(new Texture2d("mapple", "../../images/trees/mapple.png"));
        EntityManager::add(new Texture2d("oak", "../../images/trees/oak.png"));
        EntityManager::add(new Texture2d("pin", "../../images/trees/pin.png"));
        EntityManager::add(new Texture2d("sequoia", "../../images/trees/sequoia.png"));

        EntityManager::add(new Texture2d("fondation", "../../images/fondation.png"));
        EntityManager::add(new Texture2d("wall", "../../images/wall.png"));
        EntityManager::add(new Texture2d("human", "../../images/human.png"));
        EntityManager::add(new Texture2d("clouds", "../../images/clouds.png"));
        EntityManager::add(new Texture2d("simcoinminer", "../../images/simcoinminer.png"));

        //Textures boutons settings
        EntityManager::add(new Texture2d("FPSButton", "../../images/BoutonNO.png"));
        EntityManager::add(new Texture2d("FPSButtonNO", "../../images/BoutonNO.png"));
        EntityManager::add(new Texture2d("FPSButtonYES", "../../images/BoutonYES.png"));
        EntityManager::add(new Texture2d("backButton", "../../images/BoutonBack.png"));
        EntityManager::add(new Texture2d("FondSettings", "../../images/SettingsMenu.png"));
        EntityManager::add(new Texture2d("BackButtonOver", "../../images/backOver.png"));
        EntityManager::add(new Texture2d("FPSButtonYESOVER", "../../images/BoutonYESOver.png"));
        EntityManager::add(new Texture2d("FPSButtonNOOVER", "../../images/BoutonNOOver.png"));

        //Textures menu Highscore
        EntityManager::add(new Texture2d("FondHighscore", "../../images/MenuHighScore.png"));

        //Textures Pause Menu
        EntityManager::add(new Texture2d("PauseQuitGame", "../../images/PauseQuitGame.png"));
        EntityManager::add(new Texture2d("PauseQuitGameOver", "../../images/PauseQuitGameOver.png"));
        EntityManager::add(new Texture2d("PauseResumeGame", "../../images/PauseResumeGame.png"));
        EntityManager::add(new Texture2d("PauseResumeGameOver", "../../images/PauseResumeGameOver.png"));
        EntityManager::add(new Texture2d("PauseSettings", "../../images/PauseSettings.png"));
        EntityManager::add(new Texture2d("PauseSettingsOver", "../../images/PauseSettingsOver.png"));
        EntityManager::add(new Texture2d("PauseMenuFond", "../../images/PauseMenuFond.png"));
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
        if (FPSchrono.getElapsed(MICROSECONDS) > 1000000.0) { /// le chrono se remet à zéro dans la boucle run()
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
        //glCullFace(GL_FRONT_AND_BACK);

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
        sceneMap["World"] = new World("", 0, 0, 0, 20, {0, 0, 0});

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

            if (((Scene::getActiveScene() != "Quit") && (sceneDisplay != sceneMap[Scene::getActiveScene()]))) {

                sceneDisplay->unsubscribeAll(observables);
                sceneDisplay = sceneMap[Scene::getActiveScene()];
                sceneDisplay->subscribeAll(observables);
                controller->subscribeAll(observables, controller);
            }
            if((SideWindow::switched) && (sceneDisplay == sceneMap["World"])){
                ((World*)sceneDisplay)->hud->lastSideWindowUnsubscribe(observables);
                SideWindow::switched = false;
                ((World*)sceneDisplay)->hud->sideWindowSubscribe(observables);

            }


            if((SideWindow::closed == true) && (sceneDisplay == sceneMap["World"])){
                ((World*)sceneDisplay)->hud->sideWindowUnsubscribe(observables);

                SideWindow::closed = false;
            }
            if(SideWindow::opened && (sceneDisplay == sceneMap["World"])){
                ((World*)sceneDisplay)->hud->sideWindowSubscribe(observables);
                SideWindow::opened = false;
            }
            addFloor();
            addFondation();
            createWall();
            selectWallForRoofCreation();
            if(controller->getClickMousePosition()[2] != -1){
                controller->resetClicMousePosition();
            }

            ///controle des touches
            switch (controller->getKeyDown()) {
                case SDLK_f:
                    activeCamera = false;
                    glContext->releaseInput();
                    sceneDisplay->subscribeAll(observables);
                    ((World*)sceneDisplay)->hud->sideWindowSubscribe(observables);
                    break;
                case SDLK_g:
                    activeCamera = true;
                    glContext->grabInput();
                    sceneDisplay->unsubscribeAll(observables);
                    ((World*)sceneDisplay)->hud->sideWindowUnsubscribe(observables);
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



            if (sceneDisplay == sceneMap["World"] && activeCamera)
                sceneDisplay->getCamera()->update(chrono.getElapsed(SECONDS));

            glContext->clear();

            sceneDisplay->draw();
            if(sceneDisplay == sceneMap["World"]){
                ((World*)sceneMap["World"])->hud->scrollingMenuUpdateSubscribe(observables);
            }
            if(Scene::getActiveFPS() == true)
                showFPS();
            else
                SDL_SetWindowTitle(glContext->getWindow(), "P.I. 2018");
            glContext->refresh();
	        chrono.restart();

            controller->resetClicMousePosition();

        }
    }

    void addFondation() {
        if(SideWindow::buildType == BUILD_FONDATION && SideWindow::isBuilding) {
            if(activeCamera && Scene::getActiveScene() == "World" && controller->getClickMousePosition()[2] == SDL_BUTTON_LEFT){
            World* world = ((World*)sceneDisplay);



                Vector front = world->getCamera()->getFront();
                Vector pos = world->getCamera()->getPos();
                Vector nFloor = {0.0, 2.5, 0.0};
                if (front * nFloor) {
                    double ratio = -(pos.y / front.y);
                    if (ratio > 0) {
                        Vector intersection = (front * ratio) + pos;
                        int x = round(intersection.x / 2.0);
                        int z = round(intersection.z / 2.0);
                        std::map<std::pair<int,int>, Fondation*>* fondationGrid = world->getFondations();
                        if(!(*fondationGrid)[std::make_pair(x,z)]) {
                            Fondation* fondation = new Fondation("", (double)x * 2.0, 0.0, (double)z * 2.0, false);
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
                            else
                                delete fondation;
                        }

                    }
                }




            }

        }
    }
    void addFloor(){

            if (StructureWindow::chosenStory && Scene::getActiveScene() == "World" && SideWindow::buildType == BUILD_FLOOR && SideWindow::materialType != NULLMATERIAL && SideWindow::isBuilding && activeCamera && controller->getClickMousePosition()[2] == SDL_BUTTON_LEFT) {
                World* world = ((World*)sceneDisplay);
                std::map<std::pair<int,int>, Fondation*>* fondationGrid = world->getFondations();


                Vector front = world->getCamera()->getFront();
                Vector pos = world->getCamera()->getPos();
                Vector nFloor = {0.0, 2.5, 0.0};
                unsigned int height = world->hud->getFloorHeight();
                    if( front * nFloor){
                    double ratio = -((pos.y - height) / front.y);
                    if (ratio > 0) {
                        Vector intersection = (front * ratio) + pos;
                        int x = round(intersection.x / 2.0);
                        int z = round(intersection.z / 2.0);
                        std::vector<std::map<std::pair<int,int>, Floor*>>* floorGrids = world->getFloors();



                        if( StructureWindow::chosenStory > floorGrids->size()){
                            floorGrids->push_back(std::map<std::pair<int,int>, Floor*>());
                            floorGrids->back().clear();
                        }





                        Floor* floor = new Floor("", (double)x * 2.0, world->hud->getFloorHeight(), (double)z * 2.0, false);


                        if(StructureWindow::chosenStory == 1) {
                            if ((*floorGrids)[StructureWindow::chosenStory - 1].empty()) {

                                if (StructureWindow::chosenStory == 1 && (*fondationGrid)[std::make_pair(x, z)] &&
                                    (!(*fondationGrid)[std::make_pair(x, z)]->north ||
                                     !(*fondationGrid)[std::make_pair(x, z)]->east ||
                                     !(*fondationGrid)[std::make_pair(x, z)]->south ||
                                     !(*fondationGrid)[std::make_pair(x, z)]->west)) {
                                    (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] = floor;
                                }
                            }
                            else {
                                if (!(*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] && (((*fondationGrid)[std::make_pair(x-1,z)]  || (*fondationGrid)[std::make_pair(x-2,z)] || (*fondationGrid)[std::make_pair(x ,z-1)] || (*fondationGrid)[std::make_pair(x,z - 2)] || (*fondationGrid)[std::make_pair(x + 1,z)] || (*fondationGrid)[std::make_pair(x + 2,z)] || (*fondationGrid)[std::make_pair(x,z + 1)] || (*fondationGrid)[std::make_pair(x,z + 2)]) ||(((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x + 1, z)] && (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x , z + 1)]) || ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x + 1, z)] && (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x , z - 1)]) || ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x - 1, z)] && (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x , z - 1)])  || ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x - 1 , z)] && (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x , z + 1)]) )) ) {
                                    if ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x - 1, z)]) {
                                        if (!(*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)])
                                            (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] = floor;
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)]->west = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x - 1, z)];
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x - 1, z)]->east = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x, z)];
                                    }

                                    if ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x + 1, z)]) {
                                        if (!(*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)])
                                            (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] = floor;
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)]->east = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x + 1, z)];
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x + 1, z)]->west = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x, z)];
                                    }

                                    if ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z - 1)]) {
                                        if (!(*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)])
                                            (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] = floor;
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)]->north = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x, z - 1)];
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z - 1)]->south = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x, z)];
                                    }

                                    if ((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z + 1)]) {
                                        if (!(*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)])
                                            (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] = floor;
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)]->south = (*floorGrids)[
                                                StructureWindow::chosenStory - 1][std::make_pair(x, z + 1)];
                                        (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z + 1)]->north = (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)];
                                    }

                                }

                            }
                        }
                        else{
                            if ((*floorGrids)[StructureWindow::chosenStory - 1].empty() && StructureWindow::chosenStory >= 2 &&
                                ((*floorGrids)[StructureWindow::chosenStory - 2][std::make_pair(x, z)] &&
                                 (!(*floorGrids)[StructureWindow::chosenStory - 2][std::make_pair(x, z)]->east ||
                                  !(*floorGrids)[StructureWindow::chosenStory - 2][std::make_pair(x, z)]->west ||
                                  !(*floorGrids)[StructureWindow::chosenStory - 2][std::make_pair(x, z)]->south ||
                                  !(*floorGrids)[StructureWindow::chosenStory - 2][std::make_pair(x, z)]->north))) {
                                (*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x, z)] = floor;
                            }




                        }










                        if((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x,z)])
                            world->addModel((*floorGrids)[StructureWindow::chosenStory - 1][std::make_pair(x,z)]);
                        else
                            delete floor;
                }



                    }
            }
    }

    void selectWallForRoofCreation() {
        if (Scene::getActiveScene() == "World") {

            if ((SideWindow::buildType == BUILD_ROOF && SideWindow::isBuilding) &&
                (controller->getClickMousePosition()[2] == SDL_BUTTON_RIGHT)) {

                if (!SideWindow::firstWall) {
                    PhysicsData::CollisionData previousData;
                    for (auto it = ((World *) sceneDisplay)->getWallList()->begin();
                         it != ((World *) sceneDisplay)->getWallList()->end(); it++) {
                        PhysicsData::CollisionData currentData = Physics::collideVectorOnModel(((World *) sceneDisplay)->hud->getCamera()->getPos(), ((World *) sceneDisplay)->hud->getCamera()->getFront(), (*(*it)));
                        if (currentData.collided) {
                            if (SideWindow::firstWall) {
                                if (currentData.ratio < previousData.ratio) {
                                    previousData = currentData;
                                    SideWindow::firstWall = (*it);
                                }
                            } else {
                                previousData = currentData;
                                SideWindow::firstWall = (*it);
                            }

                        }
                    }
                }
                else{
                    if (!SideWindow::secondWall && SideWindow::firstWall) {
                        PhysicsData::CollisionData previousData;
                        for (auto it = ((World *) sceneDisplay)->getWallList()->begin(); it != ((World *) sceneDisplay)->getWallList()->end(); it++) {
                            PhysicsData::CollisionData currentData = Physics::collideVectorOnModel(((World *) sceneDisplay)->hud->getCamera()->getPos(), ((World *) sceneDisplay)->hud->getCamera()->getFront(), (*(*it)));
                            if (currentData.collided) {
                                if (SideWindow::secondWall) {
                                    if (currentData.ratio < previousData.ratio) {
                                        previousData = currentData;
                                        SideWindow::secondWall = (*it);
                                    }
                                } else {
                                    previousData = currentData;
                                    SideWindow::secondWall = (*it);
                                }
                            }
                        }
                        if (SideWindow::firstWall == SideWindow::secondWall) {
                            //SideWindow::secondWall = nullptr;
                        }
                    }
                }


                if(SideWindow::firstWall && SideWindow::secondWall){
                    SideWindow::isBuilding = false;
                    SideWindow::buildType = BUILD_NOTHING;
                    bool wall1OnX = false;
                    bool wall2OnX = false;
                    double posx, posy, posz, max, width, lenght;
                    posx = posy = posz = max = width = lenght = 0.0;
                    if (SideWindow::firstWall->getMesh(0) == SideWindow::firstWall->getMesh(3))
                        wall1OnX = true;
                    if (SideWindow::secondWall->getMesh(0) == SideWindow::secondWall->getMesh(3))
                        wall2OnX = true;


                    double x1 = SideWindow::firstWall->getMesh(0);
                    double x2 = SideWindow::secondWall->getMesh(0);
                    double x3 = SideWindow::firstWall->getMesh(3);
                    double x4 = SideWindow::secondWall->getMesh(3);
                    
                    
                    
                    
                    
                    if (x1 < x3) {
                        posx = x1;
                    } else {
                        posx = x3;
                    }
                    if (posx > x2) {
                        posx = x2;
                    }
                    if (posx > x4) {
                        posx = x4;
                    }

                    if (x1 > x3) {
                        max = x1;
                    } else {
                        max = x3;
                    }
                    if (max < x2) {
                        max = x2;
                    }
                    if (max < x4) {
                        max = x4;
                    }
                    width = abs(max - posx);

                    double z1 = SideWindow::firstWall->getMesh(2);
                    double z2 = SideWindow::secondWall->getMesh(2);
                    double z3 = SideWindow::firstWall->getMesh(5);
                    double z4 = SideWindow::secondWall->getMesh(5);
                    
                    if (z1 < z3) {
                        posz = z1;
                    } else {
                        posz = z3;
                    }
                    if (posz > z2) {
                        posz = z2;
                    }
                    if (posz > z4) {
                        posz = z4;
                    }

                    if (z1 > z3) {
                        max = z1;
                    } else {
                        max = z3;
                    }
                    if (max < z2) {
                        max = z2;
                    }
                    if (max < z4) {
                        max = z4;
                    }
                    lenght = abs(max - posz);


                    double y1 = SideWindow::firstWall->getMesh(1);
                    double y2 = SideWindow::secondWall->getMesh(1);
                    double y3 = SideWindow::firstWall->getMesh(4);
                    double y4 = SideWindow::secondWall->getMesh(4);

                    if (y1 > y3) {
                        posy = y1;
                    } else {
                        posy = y3;
                    }
                    if (posy < y2) {
                        posy = y2;
                    }
                    if (posy < y4) {
                        posy = y4;
                    }
                    

                    unsigned int texture;
                    switch (SideWindow::materialType) {
                        case CARDBOARD:
                            texture = EntityManager::get<Texture2d*>("wall")->ID;
                            break;
                        case WOOD:
                            texture = EntityManager::get<Texture2d*>("daysky")->ID;
                            break;
                        case ROCK:
                            texture = EntityManager::get<Texture2d*>("daysky")->ID;
                            break;
                        case METAL:
                            texture = EntityManager::get<Texture2d*>("nightsky")->ID;
                            break;
                        case SIMTIUM:
                            texture = EntityManager::get<Texture2d*>("grass")->ID;
                            break;
                    }

                    ((World*)sceneDisplay)->addModel(new Model("", width, 3.0/*StructureWindow::height*/, lenght, posx, posy, posz, texture));
                    SideWindow::firstWall = nullptr;
                    SideWindow::secondWall = nullptr;
                }
            }



        }
    }


    void createWall(){
        if(Scene::getActiveScene() == "World")

        if (SideWindow::buildType == BUILD_WALL && SideWindow::isBuilding ) {
            if (StructureWindow::chosenStory == 0) {
                SideWindow::isBuilding = false;
                SideWindow::buildType = BUILD_NOTHING;
                std::map<std::pair<int, int>, Fondation *> *fondationGrid = ((World *) sceneDisplay)->getFondations();
                Fondation *start = (*fondationGrid)[std::make_pair(0, 0)];
                while (start->north) {
                    start = start->north;
                }
                Fondation *previousPosition = start;
                Fondation *stop;
                Fondation *currentPosition;
                std::list<Vector> corner;

                if (previousPosition->east) {
                    stop = currentPosition = previousPosition->east;
                    if (!previousPosition->west) {
                        corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                        if (!previousPosition->south) {
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                        }
                    }

                } else {
                    corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                    if (previousPosition->south) {
                        stop = currentPosition = previousPosition->south;
                        if (!previousPosition->west) {
                            corner.push_front((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                        }
                    } else {
                        corner.push_front((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                        if (previousPosition->west) {
                            stop = currentPosition = previousPosition->west;
                        } else {
                            stop = currentPosition = previousPosition;
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                        }
                    }
                }

                do
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
                                            corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                                            corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                                        }
                                    }
                                } else {
                                    previousPosition = currentPosition;
                                    currentPosition = currentPosition->east;
                                    corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
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
                while (!((start->centerPoint->x == previousPosition->centerPoint->x) &&
                         (start->centerPoint->z == previousPosition->centerPoint->z) &&
                         (stop->centerPoint->x == currentPosition->centerPoint->x) &&
                         (stop->centerPoint->z == currentPosition->centerPoint->z)));
                int size = corner.size() - 1;
                Vector first = corner.front();
                unsigned int texture;
                switch (SideWindow::materialType) {
                    case CARDBOARD:
                        texture = EntityManager::get<Texture2d *>("wall")->ID;
                        break;
                    case WOOD:
                        texture = EntityManager::get<Texture2d *>("daysky")->ID;
                        break;
                    case ROCK:
                        texture = EntityManager::get<Texture2d *>("daysky")->ID;
                        break;
                    case METAL:
                        texture = EntityManager::get<Texture2d *>("nightsky")->ID;
                        break;
                    case SIMTIUM:
                        texture = EntityManager::get<Texture2d *>("grass")->ID;
                        break;
                }

                Model *mur;
                for (int i = 0; i < size; ++i) {
                    Vector temp = corner.front();
                    corner.pop_front();
                    mur = new Model("", ((World *) sceneDisplay)->hud->getHeight(), texture, &temp, &corner.front());
                    //((World *) sceneDisplay)->addModel(mur);
                    ((World *) sceneDisplay)->addWall(mur);
                }
                mur = new Model("", ((World *) sceneDisplay)->hud->getHeight(), texture, &corner.front(), &first);
                //((World *) sceneDisplay)->addModel(mur);
                ((World *) sceneDisplay)->addWall(mur);
                if (StructureWindow::chosenStory == StructureWindow::storyAmount)
                    StructureWindow::storyAmount++;


            }


            else if(StructureWindow::chosenStory < ((World *) sceneDisplay)->getFloors()->size() + 1 && ((World *) sceneDisplay)->getFloors()[StructureWindow::chosenStory - 1].size()){
                SideWindow::isBuilding = false;
                SideWindow::buildType = BUILD_NOTHING;
                std::vector<std::map<std::pair<int, int>, Floor *>> *floorGrid = ((World *) sceneDisplay)->getFloors();
                auto it = (*floorGrid)[StructureWindow::chosenStory - 1].begin();
                Floor *start = (*floorGrid)[StructureWindow::chosenStory - 1].begin().operator*().second;
                while (start->north) {
                    start = start->north;
                }
                Floor *previousPosition = start;
                Floor *stop;
                Floor *currentPosition;
                std::list<Vector> corner;

                if (previousPosition->east) {
                    stop = currentPosition = previousPosition->east;
                    if (!previousPosition->west) {
                        corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                        if (!previousPosition->south) {
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                        }
                    }

                } else {
                    corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
                    if (previousPosition->south) {
                        stop = currentPosition = previousPosition->south;
                        if (!previousPosition->west) {
                            corner.push_front((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                        }
                    } else {
                        corner.push_front((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                        if (previousPosition->west) {
                            stop = currentPosition = previousPosition->west;
                        } else {
                            stop = currentPosition = previousPosition;
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, -1.0});
                            corner.push_back((*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                        }
                    }
                }

                do
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
                                            corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {1.0, 0.0, 1.0});
                                            corner.push_back(
                                                    (*previousPosition->centerPoint) + (Vector) {-1.0, 0.0, 1.0});
                                        }
                                    }
                                } else {
                                    previousPosition = currentPosition;
                                    currentPosition = currentPosition->east;
                                    corner.push_back((*previousPosition->centerPoint) + (Vector) {1.0, 0.0, -1.0});
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
                while (!((start->centerPoint->x == previousPosition->centerPoint->x) &&
                         (start->centerPoint->z == previousPosition->centerPoint->z) &&
                         (stop->centerPoint->x == currentPosition->centerPoint->x) &&
                         (stop->centerPoint->z == currentPosition->centerPoint->z)));
                int size = corner.size() - 1;
                Vector first = corner.front();
                unsigned int texture;
                switch (SideWindow::materialType) {
                    case CARDBOARD:
                        texture = EntityManager::get<Texture2d *>("wall")->ID;
                        break;
                    case WOOD:
                        texture = EntityManager::get<Texture2d *>("daysky")->ID;
                        break;
                    case ROCK:
                        texture = EntityManager::get<Texture2d *>("daysky")->ID;
                        break;
                    case METAL:
                        texture = EntityManager::get<Texture2d *>("nightsky")->ID;
                        break;
                    case SIMTIUM:
                        texture = EntityManager::get<Texture2d *>("grass")->ID;
                        break;
                }


                Model *mur;
                for (int i = 0; i < size; ++i) {
                    Vector temp = corner.front();
                    corner.pop_front();
                    mur = new Model("", ((World *) sceneDisplay)->hud->getHeight(), texture, &temp, &corner.front());
                    //((World *) sceneDisplay)->addModel(mur);
                    ((World *) sceneDisplay)->addWall(mur);
                }
                mur = new Model("", ((World *) sceneDisplay)->hud->getHeight(), texture, &corner.front(), &first);
                //((World *) sceneDisplay)->addModel(mur);
                ((World *) sceneDisplay)->addWall(mur);
                if (StructureWindow::chosenStory == StructureWindow::storyAmount)
                    StructureWindow::storyAmount++;


            }
        }
    }

    /// Retourne les dimensions d'un image 2D
    Vector get2DTextureSize(const char* filePath) {
        SDL_Surface* surface = IMG_Load(filePath);
        Vector size = {(double)surface->w, (double)surface->h, 0};
        SDL_FreeSurface(surface);

        return size;
    }
    /// Retourne le GlContext
    GLContext* getGlContext(){
        return glContext;
    }
};

#endif
