#ifndef KEYSMENU_H
#define KEYSMENU_H

#include "includes.h"

class KeysMenu : public Menu2d {
public:
  /// Constructeur
  KeysMenu() {
      visualEntities2d.push_back(new Image2d("MainMenuBackGround", Vector(0.0, 0.0, -2.0), EntityManager::get<Texture2d*>("MenuBackground")));
      visualEntities2d.push_back(new Label2d("MainMenuTitle", Vector(50.0, 50.0, -1.0), EntityManager::get<Font*>("fntMrRobot"), "Keys", { 0, 0, 0, 255 }));

      Button2d* button = new Button2d("ButtonBack", Vector(967.0, 575.0, 1.0), EntityManager::get<Font*>("fntButton"), "Back", {0, 0, 0}, EntityManager::get<Texture2d*>("MenuButtonBackground"), EntityManager::get<Texture2d*>("MenuButtonHover"));
      button->onClick = [this]() { Scene::popScene(); };
      visualEntities2d.push_back(button);

      sortLayers();
  }
};

#endif
