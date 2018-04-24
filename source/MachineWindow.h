
#ifndef SOURCE_MACHINEWINDOW_H
#define SOURCE_MACHINEWINDOW_H

#include "SideWindow.h"
class MachineWindow : public SideWindow{
public:

    MachineWindow(){
        modelsSideWindow["SideMenuMachine"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("MachineWindow"));

        //Building Button
        modelsSideWindow["1BuildingButtonMachine"] = new Button (930, 580, 0, 340, 60, ResourceManager::getInstance()->getTexture("BuildButton"), ResourceManager::getInstance()->getTexture("BuildButtonOver"));
        modelsSideWindow["1BuildingButtonMachine"]->onClick = [this] () {};

        modelsSideWindow["1CancelButtonMachine"] = new Button (930, 650, 0, 340, 60, ResourceManager::getInstance()->getTexture("CancelButton"), ResourceManager::getInstance()->getTexture("CancelButtonOver"));
        modelsSideWindow["1CancelButtonMachine"]->onClick = [this] () {};
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
#endif //SOURCE_MACHINEWINDOW_H
