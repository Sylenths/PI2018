/// \brief Représentation du menu echap en jeu.
/// \details Interface permettant d'accéder au menu des options en jeu et de quitter le jeu.
/// \author Antoine Legault
/// \date 27 mars 2018
/// \version 0.1
/// \warning .
/// \bug Aucun.

#ifndef SOURCE_PAUSEMENU_H
#define SOURCE_PAUSEMENU_H

#include "includes.h"

class PauseMenu : public Menu {
public:

    ///Constructeur
    PauseMenu(){
        models["PauseMenuFond"] = new Image("PauseMenuFond", 0, 0, 0, 1280, 720, EntityManager::get<Texture2d*>("PauseMenuFond")->ID);

        models["1resumeGameButton"] = new Button ("1resumeGameButton", 238, 225, 0, 786, 113, EntityManager::get<Texture2d*>("PauseResumeGame")->ID, EntityManager::get<Texture2d*>("PauseResumeGameOver")->ID);
        models["1resumeGameButton"]->onClick = [this]() {Scene::pushScene("World");};

        models["2settingsButton"] = new Button ("2settingsButton", 238, 350, 0, 786, 113, EntityManager::get<Texture2d*>("PauseSettings")->ID, EntityManager::get<Texture2d*>("PauseSettingsOver")->ID);
        models["2settingsButton"]->onClick = [this]() {Scene::pushScene("SettingsMenu");};

        models["3quitGameButton"] = new Button ("3quitGameButton", 238, 475, 0, 786, 113, EntityManager::get<Texture2d*>("PauseQuitGame")->ID, EntityManager::get<Texture2d*>("PauseQuitGameOver")->ID);
        models["3quitGameButton"]->onClick = [this]() {Scene::pushScene("MainMenu");};

    }


    /// Permet d'inscrire tous les évènements comme observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void subscribeAll(std::map <unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : models) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
    }

    /// Permet de désinscrire tous les observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : models) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);
        }
    }
};


#endif
