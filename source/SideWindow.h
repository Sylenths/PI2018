/// \brief Représentation d'une fenêtre de coté pour le InGameOverlay
/// \details classe abstraite représentant une fenêtre de coté.
/// \author Guillaume Julien - Desmarchais, Antoine Legault
/// \date 20 mars 2018
/// \version 0.1
/// \warning Aucun
/// \bug Aucun
#ifndef SIDEWINDOW_H
#define SIDEWINDOW_H

class SideWindow {
protected:
    std::map<std::string, Model*> modelsSideWindow;   ///< Liste des models à afficher.




public:
    static std::string actionButton;
    static std::string getClic(){
        return actionButton;
    }


    /// Inscription des modèles aux événements.
    /// \param observables Événements.
    virtual void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;

    /// Désinscription des modèles aux événements.
    /// \param observables Événements.
    virtual void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) = 0 ;

    virtual void draw(){
        for (auto it : modelsSideWindow)
            it.second->draw();
    }

    ~SideWindow(){
        for (auto it : modelsSideWindow)
            delete it.second;
    }

};
std::string SideWindow::actionButton = "";

#endif //SIDEWINDOW_H
