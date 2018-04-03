//
// Created by etudiant on 18-04-03.
//

#ifndef SOURCE_SCENE_H
#define SOURCE_SCENE_H

#include "Observable.h"
class Scene{
protected:
    static std::string activeScene;
public:
    static std::string getActiveScene() {
        return activeScene;
    }
    virtual void draw () = 0;
    virtual void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>* observables) = 0;

    virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>* observables) = 0;
};
std::string Scene::activeScene = "MainMenu";

#endif //SOURCE_SCENE_H
