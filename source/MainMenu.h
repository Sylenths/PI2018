/// \brief Menu principal.
/// \details Interface graphique utilisateur du menu principal.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1

#ifndef MAINMENU_H
#define MAINMENU_H

#include "includes.h"

class MainMenu : public Menu2d {
public:
    /// Constructeur
    MainMenu(){
        entities2d["FondMaison"] = new Image2d("BackgroundMainMenu", "../../images/maisonApp.png", Vector(0.0, 0.0, 0.0));

        entities2d["ButtonStart"] = new Button2d("ButtonStart", Vector(967.0, 50.0, 0.0), "../../images/start.png");
        entities2d["ButtonStart"]->onClick = [this]() { Scene::changeActiveScene("World"); };

        entities2d["ButtonSettings"] = new Button2d("ButtonSettings", Vector(967, 225, 0), "../../images/settings.png");
        entities2d["ButtonSettings"]->onClick = [this]() { Scene::changeActiveScene("SettingsMenu"); };

        entities2d["ButtonHighScore"] = new Button2d("ButtonHighScore", Vector(967, 400, 0), "../../images/highscore.png");
        entities2d["ButtonHighScore"]->onClick = [this]() { Scene::changeActiveScene("HighScoresMenu"); };

        entities2d["ButtonQuitGame"] = new Button2d("ButtonQuitGame", Vector(967, 575, 0), "../../images/QuitGameOver.png");
        entities2d["ButtonQuitGame"]->onClick = [this]() { Scene::changeActiveScene("Quit"); };
    }

    /// Permet d'inscrire tous les évènements comme observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void subscribeAll(std::map <unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();

        observables[SDL_MOUSEBUTTONDOWN]->subscribe(entities2d["ButtonStart"]);
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(entities2d["ButtonSettings"]);
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(entities2d["ButtonHighScore"]);
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(entities2d["ButtonQuitGame"]);
    }

    /// Permet de désinscrire tous les observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){        
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(entities2d["ButtonStart"]);
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(entities2d["ButtonSettings"]);
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(entities2d["ButtonHighScore"]);
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(entities2d["ButtonQuitGame"]);
    }
};

#endif
