/// \brief Représentation de la fenêtre de construction des structures
/// \details Permet de choisir le matériel pour les planchers, murs et les toits et la hauteur des murs.
/// \author Guillaume Julien - Desmarchais, Antoine Legault
/// \date 20 mars 2018
/// \version 0.1
/// \warning Aucun
/// \bug Aucun
#ifndef STRUCTUREWINDOW_H
#define STRUCTUREWINDOW_H

#include "includes.h"

class StructureWindow : public SideWindow{
public:
    StructureWindow(){
        modelsSideWindow["SideMenuStructure"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("StructureWindow"));

        modelsSideWindow["1FondationIcon"] = new CheckBox (970, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1FondationIcon"]->onClick = [this] () {};
        modelsSideWindow["1FondationLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(), {128,128,128,0}, "Fonda", 970, 150, 0, 50, 20);

        modelsSideWindow["1MurIcon"] = new CheckBox (1040, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1MurIcon"]->onClick = [this] () {};
        modelsSideWindow["1MurLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(), {128,128,128,0}, "Mur", 1040, 150, 0, 50, 20);

        modelsSideWindow["1PlancherIcon"] = new CheckBox (1110, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1PlancherIcon"]->onClick = [this] () {};
        modelsSideWindow["1PlanLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(), {128,128,128,0}, "Fonda", 1110, 150, 0, 50, 20);

        modelsSideWindow["1ToitIcon"] = new CheckBox (1180, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1ToitIcon"]->onClick = [this] () {};
        modelsSideWindow["1ToitLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(), {128,128,128,0}, "Fonda", 1180, 150, 0, 50, 20);

    }


    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);
        }

    }
};
#endif //STRUCTUREWINDOW_H
