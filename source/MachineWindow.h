
#ifndef SOURCE_MACHINEWINDOW_H
#define SOURCE_MACHINEWINDOW_H

#include "SideWindow.h"
//#include "ScrollingMenu.h"

class MachineWindow : public SideWindow{
    std::map<unsigned int, Button*>  menuDeroulantBoutons;
    //ScrollingMenu* scrollMenu;
    bool scrollUp;
    bool scrollDown;
public:

    MachineWindow(){
        modelsSideWindow["SideMenuMachine"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("MachineWindow"));

        //Building Button
        modelsSideWindow["1BuildingButtonMachine"] = new Button (930, 580, 0, 340, 60, ResourceManager::getInstance()->getTexture("BuildButton"), ResourceManager::getInstance()->getTexture("BuildButtonOver"));
        modelsSideWindow["1BuildingButtonMachine"]->onClick = [this] () {};

        modelsSideWindow["1CancelButtonMachine"] = new Button (930, 650, 0, 340, 60, ResourceManager::getInstance()->getTexture("CancelButton"), ResourceManager::getInstance()->getTexture("CancelButtonOver"));
        modelsSideWindow["1CancelButtonMachine"]->onClick = [this] () {onCancelClick();};

        //Création des bouttons de machine.
        menuDeroulantBoutons[0] = new Button(920,50,0,340,80, ResourceManager::getInstance()->getTexture("SimcoinsButton"), ResourceManager::getInstance()->getTexture("SimcoinsButtonOver"));
        menuDeroulantBoutons[1] = new Button(920,130,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        menuDeroulantBoutons[2] = new Button(920,210,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        menuDeroulantBoutons[3] = new Button(920,290,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        menuDeroulantBoutons[4] = new Button(920,370,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        menuDeroulantBoutons[5] = new Button(920,450,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        menuDeroulantBoutons[6] = new Button(920,530,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        menuDeroulantBoutons[7] = new Button(920,610,0,340,80, ResourceManager::getInstance()->getTexture("PanneauSolaireButton"), ResourceManager::getInstance()->getTexture("PanneauSolaireButtonOver"));
        //Création du menu déroulant.
        //scrollMenu = new ScrollingMenu(menuDeroulantBoutons,3);

    }
    void onCancelClick(){
        buildType = BUILD_NOTHING;
        materialType = NULLMATERIAL;
        isBuilding = false;
        closed = true;
    }

    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
        //scrollUp = scrollMenu->getScrollUp();
        //scrollDown = scrollMenu->getScrollDown();

        if(scrollUp){
        // subscribe les 3 boutons.
            //scrollMenu->resetScrollUp();

        }
        if(scrollDown){
            //Subscribe les 3 boutons.
            //scrollMenu->resetScrollDown();
        }

    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);

            if(scrollUp){
                // unsubscribe les 3 boutons.


            }
            if(scrollDown) {
                // unsubscribe les 3 boutons.

            }
        }



    }
    void draw(){
        //scrollMenu->draw();
        for (auto it : modelsSideWindow)
            it.second->draw();

    }

};
#endif //SOURCE_MACHINEWINDOW_H
