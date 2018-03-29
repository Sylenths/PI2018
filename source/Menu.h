/// \brief Représentation de tous les menus du jeu.
/// \details Classe virutelle.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_MENU_H
#define SOURCE_MENU_H

#include "ProjetFinal.h"


class Menu {
private:

public:
    virtual void loadMenu() = 0;
};


#endif
