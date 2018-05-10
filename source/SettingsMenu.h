/// \brief Représentation du menu des options du jeu.
/// \details Interface permettant de modifier quelques options de jouabilité.
/// \author Antoine Legault, Samuel Labelle et Patrick Singcaster
/// \date 27 mars 2018
/// \version 0.2

#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "includes.h"

class SettingsMenu : public Menu2d {
public:
    /// Constructeur
    SettingsMenu() {
        visualEntities2d.push_back(new Image2d("MainMenuBackGround", Vector(0.0, 0.0, -2.0), EntityManager::get<Texture2d*>("MenuBackground")));
        visualEntities2d.push_back(new Label2d("MainMenuTitle", Vector(50.0, 50.0, -1.0), EntityManager::get<Font*>("fntMrRobot"), "Settings", { 0, 0, 0, 255 }));

        Button2d* button = new Button2d("ButtonBack", Vector(967.0, 575.0, 1.0), EntityManager::get<Font*>("fntButton"), "Back", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        button->onClick = [this]() { Scene::changeActiveScene(previous); };
        visualEntities2d.push_back(button);

        sortLayers();
    }
};

#endif


