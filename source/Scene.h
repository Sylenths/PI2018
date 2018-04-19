#ifndef SCENE_H
#define SCENE_H


#include "Camera.h"

class Scene {
protected:
    static std::string activeScene;
    static std::string previous;
    static bool FPS;


public:

    virtual ~Scene() {}

    static std::string changeActiveScene(std::string scene){
        previous = activeScene;
        activeScene = scene;
        return activeScene;
    }

    static std::string getActiveScene() {
        return activeScene;
    }

    static bool getActiveFPS(){
        return FPS;
    }

    virtual void draw () = 0;
    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0;
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0;
    virtual Camera* getCamera(){}
};

std::string Scene::activeScene = "MainMenu";
std::string Scene::previous = " ";
bool Scene::FPS = false;

#endif
