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

class World{
private:
    std::list<Model*> modelList; ///< La liste de models à afficher
public:


    /// Ajoute un model a afficher
    /// \params model le model a ajouter
    void addModel(Model* model){
        modelList.push_back(model);
    }
    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World(){
        addModel(new Model(ResourceManager::getInstance()->getTexture("grass"),"../images/grass.obj"));
        addModel(new Model(ResourceManager::getInstance()->getTexture("sky"),"../images/sky.obj"));
    }
    /// Affichage des models
    void draw(){
        if (modelList.size()) {
            for( auto it : modelList){
                it->draw();
            }
        }
    }

};
#endif //SOURCE_WORLD_H
