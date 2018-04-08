#ifndef SCENE_H
#define SCENE_H

class Scene {
protected:
    static std::string activeScene;

public:
    static std::string getActiveScene() {
        return activeScene;
    }

    virtual void draw () = 0;
    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0;
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0;
};

std::string Scene::activeScene = "MainMenu";

#endif
