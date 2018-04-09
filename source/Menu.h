/// \brief Représentation de tous les menus du jeu.
/// \details Classe virutelle.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef MENU_H
#define MENU_H

class Menu : public Scene {
protected:
  std::map<std::string, Model*> models;

public:
  virtual ~Menu() {
    for (auto it : models)
      delete it.second;
  }

  void draw() {
    for (auto it : models)
      it.second->draw();
  }

  virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
  virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
