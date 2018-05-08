/// \brief Menu principal.
/// \details Interface graphique utilisateur du menu principal.
/// \author Antoine Legault et Patrick Singcaster
/// \date 24 mars 2018
/// \version 0.2

#ifndef MAINMENU_H
#define MAINMENU_H

#include "includes.h"

class MainMenu : public Menu2d {
private:
    Texture2d* imageBackground,
             * buttonBackground,
             * buttonHover;
public:
    /// Constructeur
    MainMenu(){
        buttonBackground = new Texture2d("MenuButtonBackground", "../../images/MainMenuButtonBackground.png");
        buttonHover = new Texture2d("MenuButtonHover", "../../images/MainMenuButtonHover.png");
        imageBackground = new Texture2d("MainMenuBackground", "../../images/maisonApp.png");

        visualEntities2d.push_back(new Image2d("MainMenuBackGround", Vector(0.0, 0.0, 0.0), imageBackground));

        Button2d* button = new Button2d("ButtonStart", Vector(967.0, 50.0, 1.0), EntityManager::get<Font*>("font - arial28"), "Start", {0, 0, 0}, buttonBackground, buttonHover);
        button->onClick = [this]() { Scene::changeActiveScene("World"); };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonSettings", Vector(967.0, 225.0, 1.0), EntityManager::get<Font*>("font - arial28"), "Settings", {0, 0, 0}, buttonBackground, buttonHover);
        button->onClick = [this]() { Scene::changeActiveScene("SettingsMenu"); };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonHighScore", Vector(967.0, 400.0, 1.0), EntityManager::get<Font*>("font - arial28"), "High Scores", {0, 0, 0}, buttonBackground, buttonHover);
        button->onClick = [this]() { Scene::changeActiveScene("HighScoresMenu"); };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonQuitGame", Vector(967.0, 575.0, 1.0), EntityManager::get<Font*>("font - arial28"), "Quit", {0, 0, 0}, buttonBackground, buttonHover);
        button->onClick = [this]() { Scene::changeActiveScene("Quit"); };
        visualEntities2d.push_back(button);

        sortLayers();
    }

    ~MainMenu() {
        delete buttonBackground;
        delete imageBackground;
    }

    /// Permet d'inscrire les observateurs aux événements.
    /// \param observables Tous les observables.
    void subscribeAll(std::map <unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        std::list<VisualEntity2d*>::iterator it = visualEntities2d.begin();
        while (++it != visualEntities2d.end()) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(*it);
            observables[SDL_MOUSEMOTION]->subscribe(*it);
        }
    }

    /// Permet d'e désinscrire les observateurs des événements.
    /// \param observables Tous les observables.
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){        
        std::list<VisualEntity2d*>::iterator it = visualEntities2d.begin();
        while (++it != visualEntities2d.end()) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(*it);
            observables[SDL_MOUSEMOTION]->unsubscribe(*it);
        }
    }
};

#endif
