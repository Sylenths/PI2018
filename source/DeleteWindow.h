/// \brief Représentation de la fenêtre de construction des structures
/// \details Active le mode destruction.
/// \author Guillaume Julien - Desmarchais
/// \date 20 mars 2018
/// \version 0.1
/// \warning (Delete Mode On) ne prend pas de e à mode.
/// \bug Aucun
#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include "SideWindow.h"
#include "includes.h"
class DeleteWindow : public SideWindow{
public:

    DeleteWindow(){
        modelsSideWindow["logoDestruction"] = new Image("logoDestruction", 700, 0, 0.1, 260, 60, ResourceManager::getTexture("deletewindow"));
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
#endif //DELETEWINDOW_H
