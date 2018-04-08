/// \brief Représentation de tous les menus du jeu.
/// \details Classe virutelle.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_MENU_H
#define SOURCE_MENU_H

#include "includes.h"

class Menu : public Scene {
public:
  virtual void draw() = 0;
  virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
  virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
