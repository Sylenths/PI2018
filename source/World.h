/// \brief Reprsentation du monde et de la partie
/// \details Contient les donnes de jeux, methodes et models pour la partie
/// \author Mickaël Grisé-Roy, Gabriel Bourdages
/// \date 2 Avril 2018
/// \version 0.1

#ifndef SOURCE_WORLD_H
#define SOURCE_WORLD_H

#include "includes.h"
#include "GLContext.h"

class World : public Scene{
private:
    std::map<std::string, Model*> modelMap; ///< La liste de models à afficher
    InGameOverlay* hud;
    Vector wind;
    unsigned int temperature, simCoin, totalPower, usedPower, sunPower, elapsedTime, buildingTime;

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
        addModel("grass", new Model(ResourceManager::getInstance()->getTexture("grass"),"../../images/grass.obj"));
        addModel("sky", new Model(ResourceManager::getInstance()->getTexture("sky"),"../../images/sky.obj"));

        //changer model en sphere
        //addModel cycle
    }

    /// Affichage des models
    void draw() {
        GLContext::setFrustum(IS3D);

        //std::map<std::string, Model*>::iterator
        for(auto it = modelMap.begin(); it != modelMap.end(); it++)
            (*it).second->draw();

        GLContext::setFrustum(IS2D);
        hud->draw();
    }

    /// Mise a jour du temps
    /// \param chrono Chrono qui calcul le temps restant
    void updateTimeLeft(Chrono* chrono) {
        hud->updateTime(buildingTime - chrono->getTime()/1000);
    }

    void buildingPhaseStart() {

    }

    void buildingPhaseStop() {

    }

    void catastrophePhaseStart() {

    }

    void catastrophePhaseStop() {

    }

    virtual void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {}
    virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {}
};
#endif //SOURCE_WORLD_H
