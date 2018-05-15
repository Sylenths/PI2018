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

#include "Eolienne.h"
#include "Wall.h"
#include "Roof.h"

#include "PowerManager.h"
#include "SIMCoinMiner.h"
#include "Physics.h"


class World : public Scene{
private:
    GLContext* context;
    std::list<Model*> modelList; ///< La liste de models à afficher

    std::list<Wall*> wallList; ///< La liste de murs à afficher
    std::list<Roof*> roofList; ///< La liste de toits à afficher

    std::list<PowerDevice*> powerDeviceList;
    std::list<PowerSource*> powerSourceList;

    std::map<std::pair<int,int>, Fondation*> fondationGrid;///< Map Qui prend une clé de pair qui sont les 2 coordonnées en x et z des fondations qui seront crées.
    std::vector<std::map<std::pair<int,int>,Floor*>> floorGrids;
    Atmosphere atmosphere;
    Vector* wind;
    unsigned int  simCoin, totalPower, usedPower, sunPower, elapsedTime, buildingTime;
    double windspeed, temperature, producedCurrent;
    Light *hudLight;
    Chrono chrono;
    std::list<Meteorite *> meteorites;
    bool structureWasModified;
public:
    Model* flatGround;
    InGameOverlay* hud;

    /// Ajoute un model a afficher
    /// \param model le model a ajouter
    /// \param modelKey Nom donne au model
    void addModel(Model* model){
        modelList.push_back(model);
    }


    void addPowerDeviceAppariel(PowerDevice* powerDevice){
        powerDeviceList.push_back(powerDevice);
    }

    void addPowerSourceAppariel(PowerSource* powerSource){
        powerSourceList.push_back(powerSource);
    }

    void addWall(Wall* model){
        wallList.push_back(model);
    }
    void addRoof(Roof* model){
        roofList.push_back(model);
    }

    std::list<Wall*>* getWallList(){
        return &wallList;
    }
    std::list<Roof*>* getRoofList(){
        return &roofList;
    }
    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World(const std::string name, GLContext* context, unsigned int temperature, unsigned int sunPower, unsigned int simCoin, unsigned int buildingTime, Vector* wind) : atmosphere(name, 0.0, 0.0, 0.0, false, 0, "../../models/obj/atmosphere.obj") {
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
        structureWasModified = false;

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

        hudLight = new Light(0.0, 0.0, 1.0, 0.0);
        meteorites.push_back(new Meteorite(1,{0.5, 50.,0.5},{0., 10.,0.}));
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

        for(auto it = wallList.begin(); it != wallList.end(); it++)
            (*it)->drawAndShading(atmosphere.getRealLight().getVectorLight());

        for(auto it = roofList.begin(); it != roofList.end(); it++)
            (*it)->drawAndShading(atmosphere.getRealLight().getVectorLight());
        for(auto it : meteorites)
            it->drawAndShading(atmosphere.getRealLight().getVectorLight());

        collideMeteorites();
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
            addPowerDeviceAppariel(new SIMCoinMiner (5.0, "SimCoinsMiner", positionX, positionY, positionZ,  EntityManager::get<Texture2d*>("simcoinminer")->ID, true, "../../models/obj/simcoin_miner.obj"));
            addModel(powerDeviceList.back());
            powerDeviceList.back()->setShadingOn();
            PowerManager::getInstance()->addAppareil(powerDeviceList.back());
        }
        if(SideWindow::MachineType == "PanneauSolaire"){
            addPowerSourceAppariel(new PanneauSolaire("SolarPannel", positionX, positionY, positionZ, true, "../../models/obj/solarPanel2.0.obj"));
            addModel(powerSourceList.back());
            PowerManager::getInstance()->addSource(powerSourceList.back());
        }
        if(SideWindow::MachineType == "WindTurbine"){
            addPowerSourceAppariel(new Eolienne(wind, windspeed, temperature, producedCurrent, "Eolienne", positionX, positionY, positionZ, true, "../../models/obj/windTurbineFoot.obj"));
            addModel(powerSourceList.back());
            PowerManager::getInstance()->addSource(powerSourceList.back());
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

    /*std::list<PowerDevice*> powerDeviceList;

    std::map<std::pair<int,int>, Fondation*> fondationGrid;///< Map Qui prend une clé de pair qui sont les 2 coordonnées en x et z des fondations qui seront crées.
    std::vector<std::map<std::pair<int,int>,Floor*>> floorGrids;*/
    void collideMeteorites(){
        if(!meteorites.empty()){
            for( auto meteorITe : meteorites){
                bool collided = false;
                for(auto wallIt : wallList){
                    if(!collided) {
                        if (Physics::isModelWithinSphere(meteorITe->centerPos,meteorITe->radius,(*wallIt))) {
                            explodeMeteorite(meteorITe);
                            Meteorite* temp = meteorITe;
                            meteorites.remove(meteorITe);
                            delete temp;
                            collided = true;
                        }
                    }
                }
                for(auto roofIt : roofList){
                    if(!collided) {

                        if (Physics::isModelWithinSphere(meteorITe->centerPos,meteorITe->radius,(*roofIt))) {
                            explodeMeteorite(meteorITe);
                            Meteorite *temp = meteorITe;
                            meteorites.remove(meteorITe);
                            delete temp;
                            collided = true;

                        }
                    }
                }
                for(auto modelIt : modelList){
                    if(!collided) {

                        if (Physics::isModelWithinSphere(meteorITe->centerPos,meteorITe->radius,(*modelIt))) {
                            explodeMeteorite(meteorITe);
                            Meteorite *temp = meteorITe;
                            meteorites.remove(meteorITe);
                            delete temp;
                            collided = true;
                        }
                    }
                }
                for(auto it : powerDeviceList){
                    if(!collided) {

                        if (Physics::isModelWithinSphere(meteorITe->centerPos,meteorITe->radius,(*it))) {
                            explodeMeteorite(meteorITe);
                            Meteorite *temp = meteorITe;
                            meteorites.remove(meteorITe);
                            delete temp;
                            collided = true;

                        }
                    }
                }

            }
        }
    }
    void explodeMeteorite(Meteorite* meteorite){
        // p = mv, en d<autres mot puisque la seule chose qui fait varier la masse de la meteorite est son rayon on fera rayon * ||v||
        double explosionRadius = meteorite->radius * (meteorite->speed.getNorm() / 10);
        for(auto wallIt : wallList){
            if (Physics::isModelWithinSphere(meteorite->centerPos,explosionRadius,(*wallIt))){
                Wall* temp = wallIt;
                wallList.remove(wallIt);
                delete temp;
            }
        }
        for(auto roofIt : roofList){
            if (Physics::isModelWithinSphere(meteorite->centerPos,explosionRadius,(*roofIt))){
                Roof* temp = roofIt;
                roofList.remove(roofIt);
                delete temp;
            }

        }

        for(auto it : powerDeviceList){
            if (Physics::isModelWithinSphere(meteorite->centerPos,explosionRadius,(*it))){
                PowerDevice* temp = it;
                powerDeviceList.remove(it);
                delete temp;
            }
        }
    }

    bool wasStructureModified(){
        return structureWasModified;
    }
    void setStructureWasModified(bool wasIt){
        structureWasModified = wasIt;
    }


};
#endif //SOURCE_WORLD_H
