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
        glDisable(GL_DEPTH_TEST);

        for (auto it : entities2d)
            if (it.second->visible)
                it.second->draw();

        glEnable(GL_DEPTH_TEST);
    }

    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
