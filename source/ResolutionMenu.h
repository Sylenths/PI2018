/// \brief Représentation du menu des résolutions.
/// \details Interface permettant de modifier la résolution de la fenêtre.
/// \author Patrick Singcaster
/// \date 9 mai 2018
/// \version 0.1

#ifndef RESOLUTIONMENU_H
#define RESOLUTIONMENU_H

#include "includes.h"

class ResolutionMenu : public Menu2d {
private:
    GLContext* context;

public:
    /// Constructeur
    ResolutionMenu(GLContext* context) {
        this->context = context;

        visualEntities2d.push_back(new Image2d("MainMenuBackGround", Vector(0.0, 0.0, -2.0), EntityManager::get<Texture2d*>("MenuBackground")));
        visualEntities2d.push_back(new Label2d("MainMenuTitle", Vector(50.0, 50.0, -1.0), EntityManager::get<Font*>("fntMrRobot"), "Resolution", { 0, 0, 0, 255 }));

        Button2d* button = new Button2d("ButtonResolution", Vector(967.0, 50.0, 1.0), EntityManager::get<Font*>("fntButton"), "1280 x 720", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        //button->onClick = [this]() { };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonKeys", Vector(967.0, 225.0, 1.0), EntityManager::get<Font*>("fntButton"), "1440 x 900", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        //button->onClick = [this]() { };
        visualEntities2d.push_back(button);

        button = new Button2d("ButtonBack", Vector(967.0, 575.0, 1.0), EntityManager::get<Font*>("fntButton"), "Back", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
        button->onClick = [this]() { Scene::popScene(); };
        visualEntities2d.push_back(button);

        sortLayers();
    }
};

#endif
