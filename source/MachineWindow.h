
#ifndef SOURCE_MACHINEWINDOW_H
#define SOURCE_MACHINEWINDOW_H

#include "SideWindow.h"
class MachineWindow : public SideWindow{
public:

    MachineWindow(){
        modelsSideWindow["SideMenuMachine"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("MachineWindow"));
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
