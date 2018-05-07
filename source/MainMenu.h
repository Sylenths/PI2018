/// \brief Menu principal.
/// \details Interface graphique utilisateur du menu principal.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1

#ifndef SOURCE_MAINMENU_H
#define SOURCE_MAINMENU_H

class MainMenu : public Menu {
public:
    /// Constructeur
    MainMenu(){
        models["FondMaison"] = new Image("FondMaison", 0, 0, 0, 1280, 720, ResourceManager::getTexture("FondMaison"));

        models["ButtonStart"] = new Button ("ButtonStart", 967, 50, 0, 298, 128, ResourceManager::getTexture("ButtonStartOver"), ResourceManager::getTexture("ButtonStart"));
        models["ButtonStart"]->onClick = [this]() { Scene::changeActiveScene("World"); };

        models["ButtonSettings"] = new Button("ButtonSettings", 967, 225, 0, 298, 128, ResourceManager::getTexture("ButtonSettingsOver"), ResourceManager::getTexture("ButtonSettings"));
        models["ButtonSettings"]->onClick = [this]() { Scene::changeActiveScene("SettingsMenu"); };

        models["ButtonHighScore"] = new Button("ButtonHighScore", 967, 400, 0, 298, 128, ResourceManager::getTexture("ButtonHighScoreOver"), ResourceManager::getTexture("ButtonHighScore"));
        models["ButtonHighScore"]->onClick = [this]() { Scene::changeActiveScene("HighScoresMenu"); };

        models["ButtonQuitGame"] = new Button("ButtonQuitGame", 967, 575, 0, 298, 128, ResourceManager::getTexture("ButtonQuitGame"), ResourceManager::getTexture("ButtonQuitGameOver"));
        models["ButtonQuitGame"]->onClick = [this]() { Scene::changeActiveScene("Quit"); };
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
