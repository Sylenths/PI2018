#ifndef MENU2D_H
#define MENU2D_H

#include "includes.h"

class Menu2d : public Scene {
protected:
    std::list<VisualEntity2d*> visualEntities2d; ///< Liste des entités visuels 2D à afficher.

public:
    virtual ~Menu2d() {
        for (auto it : visualEntities2d)
            delete it;
    }

    virtual void draw() {
        glDisable(GL_DEPTH_TEST);

        for (auto it : visualEntities2d)
            if (it->visible)
                it->draw();

        glEnable(GL_DEPTH_TEST);
    }

    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
