//
// Created by Mic on 2018-04-02.
//
/// \brief Contient les models a afficher
/// \details Classe qui contient une liste de models 3d a afficher
/// \author Mickaël Grisé-Roy
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

public:


    /// Ajoute un model a afficher
    /// \params model le model a ajouter
    void addModel(std::string modelKey, Model* model){
        modelMap[modelKey] = model;
    }
    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World() {
        hud = new InGameOverlay();
        addModel("grass", new Model(ResourceManager::getInstance()->getTexture("grass"),"../../images/grass.obj"));
        addModel("sky", new Model(ResourceManager::getInstance()->getTexture("sky"),"../../images/sky.obj"));

    }
    /// Affichage des models
    void draw() {
        /*GLContext::setFrustum(IS3D);

        //std::map<std::string, Model*>::iterator
        for(auto it = modelMap.begin(); it != modelMap.end(); it++)
            (*it).second->draw();
        */
        GLContext::setFrustum(IS2D);
        hud->draw();
    }

    virtual void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*> *observables) {

    }

    virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*> * observables) {

    }

};
#endif //SOURCE_WORLD_H
