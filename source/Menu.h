/// \brief Représentation de tous les menus du jeu.
/// \details Classe virutelle.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_MENU_H
#define SOURCE_MENU_H

#include <list>

#include "Model.h"

class Menu {
private:
    std::list<Model*>* models; ///< Liste de modèles qui permet d'accéder aux différents éléments de l'affichage

public:
    /// Constructeur
    Menu() {
        models = new std::list<Model*>;
    }

    /// Destructeur
    ~Menu() {
        while(models)
            models->remove(0);
        delete models;
    }

    virtual void loadMenu() = 0;
};


#endif
