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
        modelsSideWindow["SideMenuWire"] = new Image("SideMenuWire", 920, 0, 0, 360, 720, EntityManager::get<Texture2d*>("CableWindow")->ID);

        //type matériaux
        modelsSideWindow["1CuivreIcon"] = new CheckBox ("1CuivreIcon", 1000, 90, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1CuivreIcon"]->onClick = [this] () {onCopperClick();};
        modelsSideWindow["1CuivreLabel"] = new Label("1CuivreLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Cuivre", 1000, 150, 0);
        modelsSideWindow["1CuivreDesc"] = new TextWindow("1CuivreDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::cuivre->getDescription(), 925, 300, 0, 135, 300, modelsSideWindow["1CuivreIcon"]);


        modelsSideWindow["1ArgentIcon"] = new CheckBox ("1ArgentIcon", 1160, 90, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1ArgentIcon"]->onClick = [this] () {onSilverClick();};
        modelsSideWindow["1ArgentLabel"] = new Label("1ArgentLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Argent", 1160, 150, 0);
        modelsSideWindow["1ArgentDesc"] = new TextWindow("1ArgentDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::argent->getDescription(), 925, 300, 0, 135, 300, modelsSideWindow["1ArgentIcon"]);


        //Building Button
        modelsSideWindow["1BuildingButtonWire"] = new Button ("1BuildingButtonWire", 930, 580, 0, 340, 60, EntityManager::get<Texture2d*>("BuildButton")->ID, EntityManager::get<Texture2d*>("BuildButtonOver")->ID);
        modelsSideWindow["1BuildingButtonWire"]->onClick = [this] () {onBuildClick();};

        modelsSideWindow["1CancelButtonWire"] = new Button ("1CancelButtonWire", 930, 650, 0, 340, 60, EntityManager::get<Texture2d*>("CancelButton")->ID, EntityManager::get<Texture2d*>("CancelButtonOver")->ID);
        modelsSideWindow["1CancelButtonWire"]->onClick = [this] () {onCancelClick();};
    }
    void onCancelClick(){
        buildType = BUILD_NOTHING;
        materialType = NULLMATERIAL;
        isBuilding = false;
        closed = true;
    }

    void onBuildClick(){
        if(buildType == BUILD_FONDATION ||(buildType != BUILD_NOTHING && materialType)) {
            isBuilding = true;
            SideWindow::closed = true;
        }
    }

    void onCopperClick(){
        ((CheckBox*)modelsSideWindow["1ArgentIcon"])->uncheck();
        buildType = BUILD_WIRE;
        materialType = COPPER;
    }

    void onSilverClick(){
        ((CheckBox*)modelsSideWindow["1CuivreIcon"])->uncheck();
        buildType = BUILD_WIRE;
        materialType = SILVER;

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
