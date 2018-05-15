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
    static int buildType;
    static int materialType;
    static bool isBuilding;
    static bool closed;
    static bool opened;
    static bool switched;
    static bool isBuildingMachine;
    static Model* firstWall;
    static Model* secondWall;
    static std::string MachineType;


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
    virtual unsigned getFloorHeight(){}
    virtual unsigned int getHeight(){}
    virtual std::map<unsigned int, unsigned int>* getWallheight(){}
};
int SideWindow::buildType = 0;
int SideWindow::materialType = 0;
bool SideWindow::isBuilding = false;
bool SideWindow::closed = false;
bool SideWindow::opened = false;
bool SideWindow::switched = false;
bool SideWindow::isBuildingMachine = false;
Model* SideWindow::firstWall = nullptr;
Model* SideWindow::secondWall = nullptr;
std::string SideWindow::MachineType = "";



#endif //SIDEWINDOW_H
