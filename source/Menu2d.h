#ifndef MENU2D_H
#define MENU2D_H

#include "includes.h"

class Menu2d : public Scene {
private:
    static bool compareVisualEntity2d(VisualEntity2d* e1, VisualEntity2d* e2) {
        return e1->position.z < e2->position.z;
    }

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

    void sortLayers() {
        visualEntities2d.sort(compareVisualEntity2d);
    }

    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
