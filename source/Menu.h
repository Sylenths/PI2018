/// \brief Représentation de menu.
/// \author Antoine Legault, Patrick Singcaster
/// \date 24 mars 2018
/// \version 0.3

#ifndef MENU_H
#define MENU_H

class Menu : public Scene {
protected:
    std::map<std::string, Model*> models; ///< Liste des models à afficher.

public:
    /// Destructeur
    virtual ~Menu() {
        for (auto it : models)
            delete it.second;
    }

    /// Affichage de tous les modèles.
    virtual void draw() {
        for (auto it : models)
            it.second->draw();
    }

    /// Inscription des modèles aux événements.
    /// \param observables Événements.
    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;

    /// Désinscription des modèles aux événements.
    /// \param observables Événements.
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;
};

#endif
