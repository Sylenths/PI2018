/// \brief Représentation du menu principal en jeu.
/// \details Interface qui apparait lorsqu'on ouvre le jeu.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef SOURCE_MAINMENU_H
#define SOURCE_MAINMENU_H

class MainMenu : public Menu {
public:

    /// Constructeur
    MainMenu(){
        models["FondMaison"] = new Image(0, 0, 0, 1280, 720, ResourceManager::getInstance()->getTexture("FondMaison"));

        models["ButtonStart"] = new Button (967, 50, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonStartOver"), ResourceManager::getInstance()->getTexture("ButtonStart"));
        models["ButtonStart"]->onClick = [this]() { Scene::changeActiveScene("World"); };

        models["ButtonSettings"] = new Button(967, 225, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonSettingsOver"), ResourceManager::getInstance()->getTexture("ButtonSettings"));
        models["ButtonSettings"]->onClick = [this]() { Scene::changeActiveScene("Settings"); };

        models["ButtonHighScore"] = new Button(967, 400, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonHighScoreOver"), ResourceManager::getInstance()->getTexture("ButtonHighScore"));
        models["ButtonHighScore"]->onClick = [this]() { Scene::changeActiveScene("Highscore"); };

        models["ButtonQuitGame"] = new Button(967, 575, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonQuitGame"), ResourceManager::getInstance()->getTexture("ButtonQuitGameOver"));
        models["ButtonQuitGame"]->onClick = [this]() { Scene::activeScene == "Quit"; };
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
