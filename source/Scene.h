//
// Created by etudiant on 18-04-03.
//

#ifndef SOURCE_SCENE_H
#define SOURCE_SCENE_H
class Scene{
protected:
    static std::string activeScene;
public:
    static std::string getActiveScene() {
        return activeScene;
    }
    virtual void draw () = 0;
};
std::string Scene::activeScene = "MainMenu";

#endif //SOURCE_SCENE_H
