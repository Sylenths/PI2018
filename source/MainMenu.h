/// \brief Menu principal.
/// \details Interface graphique utilisateur du menu principal.
/// \author Antoine Legault et Patrick Singcaster
/// \date 24 mars 2018
/// \version 0.2

#ifndef MAINMENU_H
#define MAINMENU_H

#include "includes.h"

class MainMenu : public Menu2d {
public:
    /// Constructeur
    MainMenu(){
        visualEntities2d.push_back(new Image2d("MainMenuBackGround", Vector(0.0, 0.0, -2.0), EntityManager::get<Texture2d*>("MenuBackground")));
        visualEntities2d.push_back(new Label2d("MainMenuTitle", Vector(50.0, 50.0, -1.0), EntityManager::get<Font*>("fntMrRobot"), "SIMstruction", { 0, 0, 0, 255 }));

        Button2d* button = new Button2d("ButtonStart", Vector(967.0, 50.0, 1.0), EntityManager::get<Font*>("fntButton"), "Start", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        button->onClick = [this]() { Scene::pushScene("World"); };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonSettings", Vector(967.0, 225.0, 1.0), EntityManager::get<Font*>("fntButton"), "Settings", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        button->onClick = [this]() { Scene::pushScene("SettingsMenu"); };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonHighScore", Vector(967.0, 400.0, 1.0), EntityManager::get<Font*>("fntButton"), "High Scores", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        button->onClick = [this]() { Scene::pushScene("HighScoresMenu"); };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonQuitGame", Vector(967.0, 575.0, 1.0), EntityManager::get<Font*>("fntButton"), "Quit", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        button->onClick = [this]() { Scene::pushScene("Quit"); };
        visualEntities2d.push_back(button);

        sortLayers();
    }
};

#endif
