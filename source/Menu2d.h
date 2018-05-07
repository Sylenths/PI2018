#ifndef MENU2D_H
#define MENU2D_H

#include "includes.h"

class Menu2d : public Scene {
protected:
    std::map<std::string, VisualEntity2d*> entities2d; ///< Liste des entités visuels 2D à afficher.

public:
    virtual ~Menu2d() {
        for (auto it : entities2d)
            delete it.second;
    }

    virtual void draw() {
        for (auto it : entities2d)
            if (it.second->visible)
                it.second->draw();
    }

    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
