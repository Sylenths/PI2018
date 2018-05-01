
#ifndef SOURCE_MACHINEWINDOW_H
#define SOURCE_MACHINEWINDOW_H

#include "SideWindow.h"
#include "ScrollingMenu.h"

class MachineWindow : public SideWindow{
    std::map<unsigned int, Button*>  menuDeroulantBoutons;
    ScrollingMenu* scrollMenu;
    bool scrollUp;
    bool scrollDown;
    bool openWindow;
    bool closeWindow;
public:

    MachineWindow(){
        modelsSideWindow["SideMenuMachine"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("MachineWindow"));

        //Building Button
        modelsSideWindow["1BuildingButtonMachine"] = new Button (930, 580, 0, 340, 60, ResourceManager::getInstance()->getTexture("BuildButton"), ResourceManager::getInstance()->getTexture("BuildButtonOver"));
        modelsSideWindow["1BuildingButtonMachine"]->onClick = [this] () {};

        modelsSideWindow["1CancelButtonMachine"] = new Button (930, 650, 0, 340, 60, ResourceManager::getInstance()->getTexture("CancelButton"), ResourceManager::getInstance()->getTexture("CancelButtonOver"));
        modelsSideWindow["1CancelButtonMachine"]->onClick = [this] () {onCancelClick();};

        modelsSideWindow["1UpButton"] = new Button(1260,50,0,25,45, ResourceManager::getInstance()->getTexture("UpButton"));
        modelsSideWindow["1UpButton"]->onClick = [this](){scrollMenu->ScrollUp();};

        modelsSideWindow["1DownButton"] = new Button(1260,245,0,25,45, ResourceManager::getInstance()->getTexture("DownButton"));
        modelsSideWindow["1DownButton"]->onClick = [this](){scrollMenu->ScrollDown();};

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
        scrollMenu = new ScrollingMenu(menuDeroulantBoutons,3);
        openWindow = true;
        closeWindow = false;

    }
    void onCancelClick(){
        buildType = BUILD_NOTHING;
        materialType = NULLMATERIAL;
        isBuilding = false;
        closeWindow = closed = true;

    }
    void openWindows(){
        openWindow = true;
    }

    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
        scrollUp = scrollMenu->getScrollUp();
        scrollDown = scrollMenu->getScrollDown();

        int position = scrollMenu->getPosition();
        if(scrollUp || scrollDown || openWindow){
        // subscribe les 3 boutons.
            for (int i = 0; i < 3 ; ++i) {
                observables[SDL_MOUSEBUTTONDOWN]->subscribe(menuDeroulantBoutons[position + i]);
                observables[SDL_MOUSEMOTION]->subscribe(menuDeroulantBoutons[position + i]);
            }
            scrollMenu->resetScrollUp();
            scrollMenu->resetScrollDown();
            openWindow = false;
        }

    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);

            int position = scrollMenu->getPosition();
            scrollUp = scrollMenu->getScrollUp();
            scrollDown = scrollMenu->getScrollDown();

            if(scrollUp){
                // unsubscribe les 3 boutons.
                for (int i = 0; i < 3; ++i) {
                    observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(menuDeroulantBoutons[(position+1)+i]);
                    observables[SDL_MOUSEMOTION]->unsubscribe(menuDeroulantBoutons[(position+1)+i]);
                }

            }
            if(scrollDown) {
                // unsubscribe les 3 boutons.
                for (int i = 0; i < 3 ; ++i) {
                    observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(menuDeroulantBoutons[(position-1)+i]);
                    observables[SDL_MOUSEMOTION]->unsubscribe(menuDeroulantBoutons[(position-1)+i]);
                }
            }
            if(closeWindow){
                for (int i = 0; i < 3; ++i) {
                    observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(menuDeroulantBoutons[(position+i)]);
                    observables[SDL_MOUSEMOTION]->unsubscribe(menuDeroulantBoutons[(position+i)]);
                }
                closeWindow = false;
            }
        }



    }
    void draw(){
        scrollMenu->draw();
        for (auto it : modelsSideWindow)
            it.second->draw();

    }

};
#endif //SOURCE_MACHINEWINDOW_H
