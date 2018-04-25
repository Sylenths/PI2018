/// \brief Représentation de la scène active du programme.
/// \details Permet de savoir quel menu ou quel environnement est actif.
/// \author Antoine Legault
/// \date 10 avril 2018
/// \version 0.1
/// \warning .
/// \bug Aucun.
#ifndef SCENE_H
#define SCENE_H


#include "Camera.h"

class Scene {
protected:
    static std::string activeScene;     ///< permet de savoir quel menu est actif.
    static std::string previous;        ///< permet de savoir quel était le menu précédent actif.
    static bool FPS;                    ///< permet de savoir si l'affichage des fps est actif.


public:

    static bool sceneChange;

    /// Destructeur
    virtual ~Scene() {}


    /// Permet de changer le menu affiché.
    /// \param scene le nom du nouveau menu qui sera affiché.
    static std::string changeActiveScene(std::string scene){
        previous = activeScene;
        activeScene = scene;
        return activeScene;
    }

    /// Retourner la menu actif.
    static std::string getActiveScene() {
        return activeScene;
    }

    /// Retourner un booléen "vrai" si l'affichage des fps est activé.
    static bool getActiveFPS(){
        return FPS;
    }


    /// Affiche tous les models des menus actifs.
    virtual void draw () = 0;
    /// Permet d'inscrire tous les évènements comme observables.
    /// \param observables une map contenant tous les observables nécessaires.
    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0;

    /// Permet de désinscrire tous les observables.
    /// \param observables une map contenant tous les observables nécessaires.
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0;
    /// Récupère la camera du monde.
    virtual Camera* getCamera(){}

};

std::string Scene::activeScene = "MainMenu";
std::string Scene::previous = " ";
bool Scene::FPS = false;
bool Scene::sceneChange = false;

#endif
