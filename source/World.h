/// \brief Reprsentation du monde et de la partie
/// \details Contient les donnes de jeux, methodes et models pour la partie
/// \author Mickaël Grisé-Roy, Gabriel Bourdages
/// \date 2 Avril 2018
/// \version 0.1

#ifndef SOURCE_WORLD_H
#define SOURCE_WORLD_H

#include "includes.h"
#include "GLContext.h"
#include "Camera.h"
#include "Sky.h"
#include "Atmosphere.h"
#include "Build.h"
#include "BuildWall.h"

#include "PanneauSolaire.h"
#include "PowerManager.h"
#include "SIMCoinMiner.h"

class World : public Scene{
private:
    GLContext* context;
    std::list<Model*> modelList; ///< La liste de models à afficher
    std::list<PowerAppareil*> powerApparielList;
    std::list<Model*> wallList; ///< La liste de models à afficher
    std::map<std::pair<int,int>, Fondation*> fondationGrid;///< Map Qui prend une clé de pair qui sont les 2 coordonnées en x et z des fondations qui seront crées.
    std::vector<std::map<std::pair<int,int>,Floor*>> floorGrids;
    Atmosphere atmosphere;
    Vector wind;
    unsigned int temperature, simCoin, totalPower, usedPower, sunPower, elapsedTime, buildingTime;
    Light* worldLight, * hudLight;
    Chrono chrono;
    std::list<Meteorite *> meteorites;

public:
    Model* flatGround;
    InGameOverlay* hud;

    int test;
    /// Ajoute un model a afficher
    /// \param model le model a ajouter
    /// \param modelKey Nom donne au model
    void addModel(Model* model){
        modelList.push_back(model);
    }

    void addPowerAppariel(PowerAppareil* powerAppareil){
        powerApparielList.push_back(powerAppareil);
    }

    void addWall(Model* model){
        modelList.push_back(model);
        wallList.push_back(model);
    }

    std::list<Model*>* getWallList(){
        return &wallList;
    }

    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World(const std::string name, GLContext* context, unsigned int temperature, unsigned int sunPower, unsigned int simCoin, unsigned int buildingTime, Vector wind) : atmosphere(name, 0.0, 0.0, 0.0, false, 0, "../../models/obj/atmosphere.obj") {
        this->context = context;
        this->wind = wind;
        this->temperature = temperature;
        this->sunPower = sunPower;
        this->simCoin = simCoin;
        this->buildingTime = buildingTime;
        totalPower = 0;
        usedPower = 0;
        elapsedTime = 0;
        fondationGrid[std::make_pair(0,0)]= new Fondation("", 0,0,0,false);
        hud = new InGameOverlay(0, simCoin, temperature, sunPower, wind, 0);
        addModel(fondationGrid[std::make_pair(0,0)]);
        flatGround =  new Model("", 0.0, 0.0, 0.0, EntityManager::get<Texture2d*>("grass")->ID, false, "../../models/obj/grass.obj");
        addModel(flatGround);
        test = 0;

        // Génération d'une forêt de 300 arbres...
        for (int i = 0; i < 300; i++) {
          double x = rand() % 800 - 400, z = rand() % 800 - 400;
          while (std::sqrt(x * x + z * z) < 50) {
            x = rand() % 800 - 400;
            z = rand() % 800 - 400;
          }




          switch(rand() % 8) {
            case 0: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 1: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("cerisier")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 2: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("fraksinus")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 3: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("gongko")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 4: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("mapple")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 5: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("oak")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 6: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("pin")->ID,false, "../../models/obj/tree2.0.obj")); break;
            case 7: addModel(new Model("", x, 0.0, z, EntityManager::get<Texture2d*>("sequoia")->ID,false, "../../models/obj/tree2.0.obj")); break;
          }

        }


        Model* simCoinMiner = new Model("", 100.0, 0.0, 5.0, EntityManager::get<Texture2d*>("simcoinminer")->ID, true, "../../models/obj/simcoin_miner.obj");
        simCoinMiner->setShadingOn();
        addModel(simCoinMiner);


        SIMCoinMiner* test = new SIMCoinMiner(5.0, "SimCoinsMiner", 50.0, 0.0, 5.0, EntityManager::get<Texture2d*>("simcoinminer")->ID, true, "../../models/obj/simcoin_miner.obj" );
        addModel(test);
        PowerManager::getInstance()->addAppareil(test);



        hudLight = new Light(0.0, 0.0, 1.0, 0.0);

        chrono.restart();
    }
    ~World(){
        delete hud;
        delete hudLight;
        for(auto it : modelList){
            delete it;
        }
       // for (auto it : powerApparielList)
         //   delete it;
    }
    std::map<std::pair<int,int>, Fondation*>* getFondations (){
        return &fondationGrid;
    }

    std::vector<std::map<std::pair<int,int>, Floor*>>* getFloors(){
        return &floorGrids;
    }



    /// Affichage des models
    void draw() {
        context->setFrustum(IS3D);
        glDepthFunc(GL_LEQUAL);

        hud->getCamera()->applyViewMatrix();
        atmosphere.getRealLight().applyLightPosition();

        for(auto it = modelList.begin(); it != modelList.end(); it++)
            (*it)->drawAndShading(atmosphere.getRealLight().getVectorLight());

        atmosphere.updateAtmosphere();
        atmosphere.draw();
        context->setFrustum(IS2D);
        glDepthFunc(GL_LESS);
        hudLight->applyLightPosition();
        hud->draw();
    }

    /// Mise a jour du temps dans l'H.U.D.
    /// \param chrono Chrono qui calcul le temps restant
    void updateTimeLeft(Chrono* chrono) {
       hud->updateTime(buildingTime - chrono->getElapsed(SECONDS));
    }

    void buildingPhaseStart() {

    }

    void buildingPhaseStop() {

    }

    void catastrophePhaseStart() {

    }

    void catastrophePhaseStop() {

    }
    Camera* getCamera(){
        return hud->getCamera();
    }

    void createMachine(int positionX, int positionY, int positionZ){
        if(SideWindow::MachineType == "SimCoinsMiner"){
            addPowerAppariel(new SIMCoinMiner (5.0, "SimCoinsMiner", positionX, positionY, positionZ, EntityManager::get<Texture2d*>("simcoinminer")->ID, true, "../../models/obj/simcoin_miner.obj"));
            addModel(powerApparielList.back());
            PowerManager::getInstance()->addAppareil(powerApparielList.back());
        }
        if(SideWindow::MachineType == "PanneauSolaire"){

        }

    }

    virtual void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();
        if (!observables[SDL_KEYDOWN]) observables[SDL_KEYDOWN] = new Observable<SDL_Event*>();
        hud->subscribeAll(observables);
    }
    virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        hud->unsubscribeAll(observables);
    }

    InGameOverlay* getHud(){
        return hud;
    }
    void collideMeteorites(){

    }


};
#endif //SOURCE_WORLD_H
