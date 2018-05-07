/// \brief Représentation du menu des options du jeu.
/// \details Interface permettant de modifier quelques options de jouabilité.
/// \author Antoine Legault, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "CheckBox.h"

class SettingsMenu : public Menu {
public:
    /// Constructeur
    SettingsMenu() {
        models["FondSettings"] = new Image ("FondSettings", 0, 0, 0, 1280, 720, ResourceManager::getTexture("FondSettings"));

        models["1labelActiveCamera"]       = new Label("1labelActiveCamera", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Camera on     :    G   ", 71, 200, 0.1);
        models["1labelDesactiveCamera"]    = new Label("1labelDesactiveCamera", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Camera off    :    F   ", 71, 260, 0.1);
        models["1labelPauseMenu"]          = new Label("1labelPauseMenu", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Pause menu    :    ESC   ", 71, 310,0.1);
        models["FPSLabel"]                 = new Label("FPSLabel", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Active FPS visibility  :", 71, 360, 0.1);

        models["1labelMoveForward"]        = new Label("1labelMoveForward", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Move forward  :    W   ", 650, 200, 0.1);
        models["1labelMoveBackward"]       = new Label("1labelMoveBackward", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Move backward :    S   ", 650, 260, 0.1);
        models["1labelMoveLeft"]           = new Label("1labelMoveLeft", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Move left     :    A   ", 650, 310, 0.1);
        models["1labelMoveRight"]          = new Label("1labelMoveRight", ResourceManager::getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Move right    :    D   ", 650, 360, 0.1);

        models["FPSButton"] = new CheckBox ("FPSButton", 380, 360, 0, 250, 50, ResourceManager::getTexture("FPSButtonNO"), ResourceManager::getTexture("FPSButtonYES"));
        models["FPSButton"]->onClick = [this] () {showFPS();};
        models["1backButton"]  = new Button ("1backButton", 498, 550, 0, 284, 113, ResourceManager::getTexture("backButton"), ResourceManager::getTexture("BackButtonOver"));
        models["1backButton"]->onClick = [this]() { Scene::changeActiveScene(previous); };
    }


    void showFPS(){
        if(FPS == false)
            FPS = true;
        else
            FPS = false;
    }


    /// Permet d'inscrire tous les évènements comme observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables){
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


