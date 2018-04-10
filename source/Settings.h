/// \brief Représentation du menu des options du jeu.
/// \details Interface permettant de modifier quelques options de jouabilité.
/// \author Antoine Legault, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.1
/// \warning Le bouton FPS devrait être une case à cocher.
/// \bug Aucun.

#ifndef SETTINGS_H
#define SETTINGS_H

#include "CheckBox.h"

class Settings : public Menu {
public:

    /// Constructeur
    Settings() {
        models["FondSettings"] = new Image (0, 0, 0, 1280, 720, ResourceManager::getInstance()->getTexture("FondSettings"));

        models["FPSLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(), {128,128,128,0}, "Show FPS : ", 71, 300, 0, 466, 113);

        models["FPSButton"] = new CheckBox (712, 300, 0, 510, 113, ResourceManager::getInstance()->getTexture("FPSButtonNO"), ResourceManager::getInstance()->getTexture("FPSButtonYES"));

        models["backButton"]  = new Button (498, 550, 0, 284, 113, ResourceManager::getInstance()->getTexture("backButton"), ResourceManager::getInstance()->getTexture("BackButtonOver"));
        models["backButton"]->onClick = [this]() { Scene::activeScene  = "MainMenu"; };

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


