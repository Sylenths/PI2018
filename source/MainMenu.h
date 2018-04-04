/// \brief Représentation du menu principal en jeu.
/// \details Interface qui apparait lorsqu'on ouvre le jeu.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_MAINMENU_H
#define SOURCE_MAINMENU_H

#include "Button.h"

class MainMenu : public Menu {
private:
    Button* startButton;
    Button* settingsButton;
    Button* highscoreButton;
    Image* imageMenu;

public:
    /// Constructeur
    MainMenu(){
        imageMenu = new Image( ResourceManager::getInstance()->getTexture("FondMaison"), 0, 0, 0, 1280, 720);
        ResourceManager::getInstance()->addResource("FondMaison", imageMenu);

        startButton = new Button (967, 75, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonStart"), ResourceManager::getInstance()->getTexture("ButtonStartOver"));
        ResourceManager::getInstance()->addResource("ButtonStart", startButton);
        startButton->onClick = [this]() { Scene::activeScene = "World"; };

        settingsButton = new Button(967, 275, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonSettings"), ResourceManager::getInstance()->getTexture("ButtonSettingsOver"));
        ResourceManager::getInstance()->addResource("ButtonSettings", settingsButton);
        settingsButton->onClick = [this]() { Scene::activeScene  = "Settings"; };

        highscoreButton = new Button(967, 475, 0, 298, 128, ResourceManager::getInstance()->getTexture("ButtonHighScore"), ResourceManager::getInstance()->getTexture("ButtonHighScoreOver"));
        ResourceManager::getInstance()->addResource("ButtonHighScore", highscoreButton);
        highscoreButton->onClick = [this]() { Scene::activeScene  = "Highscore"; };
    }

    ~MainMenu(){
        delete startButton;
        delete settingsButton;
        delete highscoreButton;
        delete imageMenu;
    }

    void draw(){
        startButton->draw();
        highscoreButton->draw();
        settingsButton->draw();
        imageMenu->draw();
    }

    void subscribeAll(std::map <unsigned int, Observable<SDL_Event*>*>* observables){
        if(!(*observables)[SDL_MOUSEBUTTONDOWN])
            (*observables)[SDL_MOUSEBUTTONDOWN]= new Observable<SDL_Event*>;

        if(!(*observables)[SDL_MOUSEMOTION])
            (*observables)[SDL_MOUSEMOTION]= new Observable<SDL_Event*>;

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonStart"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonStart"));

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonSettings"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonSettings"));

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonHighScore"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonHighScore"));
    }
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables){
        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonStart"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonStart"));

        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonSettings"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonSettings"));

        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonHighScore"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonHighScore"));
    }
};


#endif
