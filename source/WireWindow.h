/// \brief Représentation de la fenêtre de cablâge
/// \details Permet de décider du matériel du cable et son diamètre.
/// \author Guillaume Julien - Desmarchais, Antoine Legault
/// \date 20 mars 2018
/// \version 0.1
/// \warning Aucun
/// \bug Aucun
#ifndef WIREWINDOW_H
#define WIREWINDOW_H
class WireWindow : public SideWindow{
public:

    WireWindow(){
        modelsSideWindow["SideMenuWire"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("CableWindow"));

        //type matériaux
        modelsSideWindow["1CuivreIcon"] = new CheckBox (1000, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1CuivreIcon"]->onClick = [this] () {};
        modelsSideWindow["1CuivreLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Cuivre", 1000, 150, 0);

        modelsSideWindow["1ArgentIcon"] = new CheckBox (1160, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1ArgentIcon"]->onClick = [this] () {};
        modelsSideWindow["1ArgentLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Argent", 1160, 150, 0);

        //Building Button
        modelsSideWindow["1BuildingButtonWire"] = new Button (930, 580, 0, 340, 60, ResourceManager::getInstance()->getTexture("BuildButton"), ResourceManager::getInstance()->getTexture("BuildButtonOver"));
        modelsSideWindow["1BuildingButtonWire"]->onClick = [this] () {};

        modelsSideWindow["1CancelButtonWire"] = new Button (930, 650, 0, 340, 60, ResourceManager::getInstance()->getTexture("CancelButton"), ResourceManager::getInstance()->getTexture("CancelButtonOver"));
        modelsSideWindow["1CancelButtonWire"]->onClick = [this] () {};
    }

    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);
        }

    }
};
#endif //WIREWINDOW_H
