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

class World : public Scene{
private:
    std::map<std::string, Model*> modelMap; ///< La liste de models à afficher
    InGameOverlay* hud;
    Vector wind;
    unsigned int temperature, simCoin, totalPower, usedPower, sunPower, elapsedTime, buildingTime;
    Camera* camera;
    Light* worldLight, * hudLight;
    Matrix fanRotationMatrix;

public:
    /// Ajoute un model a afficher
    /// \param model le model a ajouter
    /// \param modelKey Nom donne au model
    void addModel(std::string modelKey, Model* model){
        modelMap[modelKey] = model;
    }

    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World(unsigned int temperature, unsigned int sunPower, unsigned int simCoin, unsigned int buildingTime, Vector wind) {
        this->wind = wind;
        this->temperature = temperature;
        this->sunPower = sunPower;
        this->simCoin = simCoin;
        this->buildingTime = buildingTime;
        totalPower = 0;
        usedPower = 0;
        elapsedTime = 0;
        hud = new InGameOverlay(0, simCoin, temperature, sunPower, wind, 0);
        addModel("grass", new Model(ResourceManager::getInstance()->getTexture("grass"),"../../models/obj/grass.obj"));
        addModel("sky", new Model(ResourceManager::getInstance()->getTexture("sky"),"../../models/obj/sky.obj"));
        addModel("fan", new Model(ResourceManager::getInstance()->getTexture("fan"),"../../models/obj/fan.obj"));

        camera = new Camera({ 0.0, 1.0, 0.0 }, { 0.0, 1.0, -1.0 }, { 0.0, 1.0, 0.0 });
        camera->loadViewMatrix();

        worldLight = new Light(0.0, 25.0, 0.0, 4.0);
        hudLight = new Light(0.0, 0.0, 1.0, 0.0);

        fanRotationMatrix.loadTranslation(Vector(0.0, 0.5, 0.0));
        modelMap["fan"]->transform(fanRotationMatrix);
        fanRotationMatrix.loadArbitraryRotation(Vector(0.0, 0.5, 0.0), Vector(0.0, 1.0, 0.0), 3.6);

    }

    /// Affichage des models
    void draw() {
        GLContext::setFrustum(IS3D);

        modelMap["fan"]->transform(fanRotationMatrix);

        camera->applyViewMatrix();
        worldLight->applyLightPosition();
        for(auto it = modelMap.begin(); it != modelMap.end(); it++)
            (*it).second->draw();

        GLContext::setFrustum(IS2D);
        hudLight->applyLightPosition();
        hud->draw();
    }

    /// Mise a jour du temps dans l'H.U.D.
    /// \param chrono Chrono qui calcul le temps restant

    /*void updateTimeLeft(Chrono<std::chrono::seconds>* chrono) {
       // hud->updateTime(buildingTime - chrono->getTime());
    }
    */

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

        observables[SDL_MOUSEMOTION]->subscribe(camera);
        observables[SDL_KEYDOWN]->subscribe(camera);
    }
    virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {}
};
#endif //SOURCE_WORLD_H
