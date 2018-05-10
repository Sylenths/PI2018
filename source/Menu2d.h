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

    /// Permet d'inscrire les observateurs aux événements.
    /// \param observables Tous les observables.
    void subscribeAll(std::map <unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        std::list<VisualEntity2d*>::iterator it = visualEntities2d.begin();
        while (it != visualEntities2d.end()) {
            if ((*it)->position.z > 0.0) {
                observables[SDL_MOUSEBUTTONDOWN]->subscribe(*it);
                observables[SDL_MOUSEMOTION]->subscribe(*it);
            }
            it++;
        }
    }

    /// Permet de désinscrire tous les observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        std::list<VisualEntity2d*>::iterator it = visualEntities2d.begin();
        while (it != visualEntities2d.end()) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(*it);
            observables[SDL_MOUSEMOTION]->unsubscribe(*it++);
        }
    }
};

#endif
