/// \brief Représentation de tous les menus du jeu.
/// \details Classe virutelle.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_MENU_H
#define SOURCE_MENU_H

class Menu {
protected:
  static std::string activeMenu;

public:  
  static std::string getActiveMenu() {
    return activeMenu;
  }

  virtual void subscribeAll() = 0;

  virtual void unsusbscribeAll() = 0;

  virtual void draw() = 0;

};

std::string Menu::activeMenu = "MainMenu";

#endif
