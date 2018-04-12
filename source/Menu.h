/// \brief Représentation de tous les menus du jeu.
/// \details Classe virutelle.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef MENU_H
#define MENU_H
#include "includes.h"
class Menu : public Scene {
protected:
  std::map<std::string, Model*> models;      ///< models Une list de différents models pour l'affichages des menus et du H.U.D.

public:
    /// Destructeur
  virtual ~Menu() {
    for (auto it : models)
      delete it.second;
  }

    /// Permet d'afficher tous les modèles utilisés dans les menus actifs.
    virtual void draw() {
    for (auto it : models)
      it.second->draw();
  }

    /// Permet d'inscrire tous les évènements comme observables.
    /// \param observables une map contenant tous les observables nécessaires.
  virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;

    /// Permet de désinscrire tous les observables.
    /// \param observables une map contenant tous les observables nécessaires.
  virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
