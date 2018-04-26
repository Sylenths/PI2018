/// \brief Représentation de la fenêtre de construction des structures
/// \details Permet de choisir le matériel pour les planchers, murs et les toits et la hauteur des murs.
/// \author Guillaume Julien - Desmarchais, Antoine Legault
/// \date 20 mars 2018
/// \version 0.1
/// \warning Aucun
/// \bug Aucun
#ifndef STRUCTUREWINDOW_H
#define STRUCTUREWINDOW_H

#include "includes.h"

class StructureWindow : public SideWindow{
private:



public:
    static unsigned  int height;
    StructureWindow(){

        height = 0;
        isBuilding = false;

        modelsSideWindow["SideMenuStructure"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("StructureWindow"));


        //type de structure
        modelsSideWindow["1FondationIcon"] = new CheckBox (970, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1FondationIcon"]->onClick = [this] () { onFoundationClick();};
        modelsSideWindow["1FondationLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Fondation", 970, 150, 0);

        modelsSideWindow["1MurIcon"] = new CheckBox (1040, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1MurIcon"]->onClick = [this] () { onWallClick();};
        modelsSideWindow["1MurLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Mur", 1040, 150, 0);

        modelsSideWindow["1PlancherIcon"] = new CheckBox (1110, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1PlancherIcon"]->onClick = [this] () {onFloorClick();};
        modelsSideWindow["1PlanLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Toit", 1110, 150, 0);

        modelsSideWindow["1ToitIcon"] = new CheckBox (1180, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1ToitIcon"]->onClick = [this] () {onRoofClick();};
        modelsSideWindow["1ToitLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Plancher", 1180, 150, 0);

        //type de matérieux
        modelsSideWindow["1CartonIcon"] = new CheckBox (940, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1CartonIcon"]->onClick = [this] () {onCardboardClick();};
        modelsSideWindow["1CartonLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Carton", 940, 265, 0);

        modelsSideWindow["1BoisIcon"] = new CheckBox (1010, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1BoisIcon"]->onClick = [this] () {onWoodClick();};
        modelsSideWindow["1BoisLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Bois", 1010, 265, 0);

        modelsSideWindow["1PierreIcon"] = new CheckBox (1080, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1PierreIcon"]->onClick = [this] () {onRockClick();};
        modelsSideWindow["1PierreLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Pierre", 1080, 265, 0);

        modelsSideWindow["1MetalIcon"] = new CheckBox (1150, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1MetalIcon"]->onClick = [this] () {onMetalClick();};
        modelsSideWindow["1MetalLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Metal", 1150, 265, 0);

        modelsSideWindow["1SIMTiumIcon"] = new CheckBox (1220, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1SIMTiumIcon"]->onClick = [this] () {onSIMTiumClick();};
        modelsSideWindow["1SIMTiumLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "SIMTium", 1220, 265, 0);


        //Building Button
        modelsSideWindow["1BuildingButtonStructure"] = new Button (930, 580, 0, 340, 60, ResourceManager::getInstance()->getTexture("BuildButton"), ResourceManager::getInstance()->getTexture("BuildButtonOver"));
        modelsSideWindow["1BuildingButtonStructure"]->onClick = [this] () {onBuildClick();};

        modelsSideWindow["1CancelButtonStructure"] = new Button (930, 650, 0, 340, 60, ResourceManager::getInstance()->getTexture("CancelButton"), ResourceManager::getInstance()->getTexture("CancelButtonOver"));
        modelsSideWindow["1CancelButtonStructure"]->onClick = [this] () {onCancelClick();};

        //Parameter
        modelsSideWindow["1AddHeight"] = new Button ( 1020, 300, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1AddHeight"]->onClick = [this] () {height++;};

        modelsSideWindow["1SoustracHeight"] = new Button (1130, 300, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1SoustracHeight"]->onClick = [this] () {height--;};

        char buffer[10];
        SDL_itoa(height, buffer, 10);

        modelsSideWindow["1HeightNumber"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0}, buffer, 1085, 300, 0);



    }
    void onBuildClick(){
        if(buildType == BUILD_FONDATION ||(buildType != BUILD_NOTHING && materialType)) {
            isBuilding = true;
            SideWindow::closed = true;
        }
    }
    void onCancelClick(){
        buildType = BUILD_NOTHING;
        materialType = NULLMATERIAL;
        isBuilding = false;
        closed = true;
    }
    void onFoundationClick(){
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        buildType = BUILD_FONDATION;
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->check();
    }

    void onWallClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        buildType = BUILD_WALL;
        ((CheckBox*)modelsSideWindow["1MurIcon"])->check();

    }
    void onFloorClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        buildType = BUILD_FLOOR;
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->check();
    }
    void onRoofClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        buildType = BUILD_ROOF;
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->check();
    }
    void onCardboardClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = CARDBOARD;
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->check();
    }
    void onWoodClick(){
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = WOOD;
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->check();
    }
    void onRockClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = ROCK;
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->check();
    }
    void onMetalClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = METAL;
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->check();
    }
    void onSIMTiumClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        materialType = SIMTIUM;
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->check();
    }






    /*char setBuffer(unsigned int){
        char buffer[10];
        SDL_itoa(height, buffer, 10);
        return buffer;
    }
*/
   /* void structureTypeCheck(std::string type, std::string modelName){
        if(structureType == "")
            structureType = type;
        else{
            modelsSideWindow["1FondationIcon"]->setTexture("",0);
            modelsSideWindow["1MurIcon"]->setTexture("",0);
            modelsSideWindow["1PlancherIcon"]->setTexture("",0);
            modelsSideWindow["1ToitIcon"]->setTexture("",0);
            modelsSideWindow[modelName]->setTexture("clic", ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        }

        actionButton = type;
    }*/

   /* void materialTypeCheck(std::string type, std::string modelName){
        if(materialType == "")
            materialType = type;
        else{
            modelsSideWindow["1CartonIcon"]->setTexture("",0);
            modelsSideWindow["1BoisIcon"]->setTexture("",0);
            modelsSideWindow["1PierreIcon"]->setTexture("",0);
            modelsSideWindow["1MetalIcon"]->setTexture("",0);
            modelsSideWindow["1SIMTiumIcon"]->setTexture("",0);
            modelsSideWindow[modelName]->setTexture("clic", ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        }
        actionButton = type;
    }*/


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
unsigned int StructureWindow::height = 0;
#endif //STRUCTUREWINDOW_H
