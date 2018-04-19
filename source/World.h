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

class World : public Scene{
private:
    std::list<Model*> modelList; ///< La liste de models à afficher
    Sky sky;
    Atmosphere atmosphere;
    InGameOverlay* hud;
    Vector wind;
    unsigned int temperature, simCoin, totalPower, usedPower, sunPower, elapsedTime, buildingTime;
    Camera* camera;
    Light* worldLight, * hudLight;
    Matrix fanRotationMatrix;
    Chrono chrono;

public:
    /// Ajoute un model a afficher
    /// \param model le model a ajouter
    /// \param modelKey Nom donne au model
    void addModel(Model* model){
        modelList.push_back(model);
    }

    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World(unsigned int temperature, unsigned int sunPower, unsigned int simCoin, unsigned int buildingTime, Vector wind) : sky(0.0, 0.0, 0.0, false, ResourceManager::getInstance()->getTexture("daysky")), atmosphere(0.0, 0.0, 0.0, false, 0) {
        this->wind = wind;
        this->temperature = temperature;
        this->sunPower = sunPower;
        this->simCoin = simCoin;
        this->buildingTime = buildingTime;
        totalPower = 0;
        usedPower = 0;
        elapsedTime = 0;
        hud = new InGameOverlay(0, simCoin, temperature, sunPower, wind, 0);

        addModel( new Model(0.0, 0.0, 0.0, ResourceManager::getInstance()->getTexture("grass"), false, "../../models/obj/grass.obj"));
        addModel(new Sky(0.0, 0.0, 0.0, ResourceManager::getInstance()->getTexture("daysky"),false, "../../models/obj/skysphere.obj"));
        addModel(new Model(0.0, 1.0, -1.0, ResourceManager::getInstance()->getTexture("fan"), true, "../../models/obj/fan.obj"));
	    addModel(new Model(0.0, 0.0, 2.0, ResourceManager::getInstance()->getTexture("simcoinminer"), true, "../../models/obj/simcoin_miner.obj"));
	    addModel(new Model(0.0, 0.0, -2.0, ResourceManager::getInstance()->getTexture("human"), true, "../../models/obj/human.obj"));

        camera = new Camera({ 0.0, 3.5, 0.0 }, { 0.0, 3.5, -1.0 }, { 0.0, 1.0, 0.0 });
        camera->loadViewMatrix();

        worldLight = new Light(0.0, 25.0, 0.0, 4.0);
        hudLight = new Light(0.0, 0.0, 1.0, 0.0);



        chrono.restart();
    }

    void checkForActions(){

        while(!hud->getActions()->empty()){
            switch (hud->getActions()->front()->getActionType()){
                case BUILD: double x = ((Build*)hud->getActions()->front())->x;
                            double y = ((Build*)hud->getActions()->front())->y;
                            double z = ((Build*)hud->getActions()->front())->z;
                            addModel(new Model(x,y,z,false,ResourceManager::getInstance()->getTexture("human"),"../../models/obj/human.obj"));
                            delete hud->getActions()->front();
                            hud->getActions()->pop();


                    break;
            }
        }
    }

    /// Affichage des models
    void draw() {
        checkForActions();
        GLContext::setFrustum(IS3D);


        sky.update(chrono);
        if(sky.getTime())
            atmosphere.darken(chrono);
        else
            atmosphere.lighten(chrono);

        camera->applyViewMatrix();
        worldLight->applyLightPosition();
        for(auto it = modelList.begin(); it != modelList.end(); it++)
            (*it)->draw();

        GLContext::setFrustum(IS2D);
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
        return camera;
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
};
#endif //SOURCE_WORLD_H
