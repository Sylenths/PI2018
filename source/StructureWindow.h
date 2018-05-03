/// \brief Représentation de la fenêtre de construction des structures
/// \details Permet de choisir le matériel pour les planchers, murs et les toits et la hauteur des murs.
/// \author Guillaume Julien - Desmarchais, Antoine Legault, Mickaël Grisé-Roy
/// \date 20 mars 2018
/// \version 1.0
/// \warning Aucun
/// \bug Aucun
#ifndef STRUCTUREWINDOW_H
#define STRUCTUREWINDOW_H

#include "includes.h"
#include "TextWindow.h"
class StructureWindow : public SideWindow{
private:
    char buffer[10];

public:
    static unsigned int storyAmount;
    static unsigned int chosenStory;
    std::vector<unsigned int> height;
    StructureWindow(){
        isBuilding = false;
        chosenStory = 0;
        storyAmount = 0;
        height.push_back(1);
        modelsSideWindow["SideMenuStructure"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("StructureWindow"));


        //type de structure
        modelsSideWindow["1FondationIcon"] = new CheckBox (970, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1FondationIcon"]->onClick = [this] () { onFoundationClick();};
        modelsSideWindow["1FondationLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Fondation", 970, 150, 0);
        modelsSideWindow["1FondationDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure de base pour permettre de construire les autres types de structure ou de machines.", 1110, 440, 0, 135, 300, modelsSideWindow["1FondationIcon"]);


        modelsSideWindow["1MurIcon"] = new CheckBox (1040, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1MurIcon"]->onClick = [this] () { onWallClick();};
        modelsSideWindow["1MurLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Mur", 1040, 150, 0);
        modelsSideWindow["1MurDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure permet de construire des murs sur tous les fondations, il faut rentrer une hauteur en parametre.", 1110, 440, 0, 135, 300, modelsSideWindow["1MurIcon"]);


        modelsSideWindow["1PlancherIcon"] = new CheckBox (1110, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1PlancherIcon"]->onClick = [this] () {onFloorClick();};
        modelsSideWindow["1PlanLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Plancher", 1110, 150, 0);
        modelsSideWindow["1PlancherDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure permet de construire des planchers sur des fondations possedant des murs, il faut rentrer l'etage sur lequel on veut travailler.", 1110, 440, 0, 135, 300, modelsSideWindow["1PlancherIcon"]);


        modelsSideWindow["1ToitIcon"] = new CheckBox (1180, 90, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1ToitIcon"]->onClick = [this] () {onRoofClick();};
        modelsSideWindow["1ToitLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Toit", 1180, 150, 0);
        modelsSideWindow["1ToitDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure permet de construire un toit sur des fondations possedant des murs.", 1110, 440, 0, 135, 300, modelsSideWindow["1ToitIcon"]);


        //type de matérieux
        modelsSideWindow["1CartonIcon"] = new CheckBox (940, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1CartonIcon"]->onClick = [this] () {onCardboardClick();};
        modelsSideWindow["1CartonLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Carton", 940, 265, 0);
        modelsSideWindow["1CartonLabelDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::carton->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1CartonIcon"]);



        modelsSideWindow["1BoisIcon"] = new CheckBox (1010, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1BoisIcon"]->onClick = [this] () {onWoodClick();};
        modelsSideWindow["1BoisLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Bois", 1010, 265, 0);
        modelsSideWindow["1BoisDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::bois->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1BoisIcon"]);


        modelsSideWindow["1PierreIcon"] = new CheckBox (1080, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1PierreIcon"]->onClick = [this] () {onRockClick();};
        modelsSideWindow["1PierreLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Pierre", 1080, 265, 0);
        modelsSideWindow["1PierreDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::pierre->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1PierreIcon"]);


        modelsSideWindow["1MetalIcon"] = new CheckBox (1150, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1MetalIcon"]->onClick = [this] () {onMetalClick();};
        modelsSideWindow["1MetalLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Metal", 1150, 265, 0);
        modelsSideWindow["1MetalDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::metal->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1MetalIcon"]);


        modelsSideWindow["1SIMTiumIcon"] = new CheckBox (1220, 205, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1SIMTiumIcon"]->onClick = [this] () {onSIMTiumClick();};
        modelsSideWindow["1SIMTiumLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, "SIMTium", 1220, 265, 0);
        modelsSideWindow["1SIMTiumDesc"] = new TextWindow(ResourceManager::getInstance()->getResource<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::simtium->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1SIMTiumIcon"]);


        //Building Button
        modelsSideWindow["1BuildingButtonStructure"] = new Button (930, 580, 0, 340, 60, ResourceManager::getInstance()->getTexture("BuildButton"), ResourceManager::getInstance()->getTexture("BuildButtonOver"));
        modelsSideWindow["1BuildingButtonStructure"]->onClick = [this] () {onBuildClick();};

        modelsSideWindow["1CancelButtonStructure"] = new Button (930, 650, 0, 340, 60, ResourceManager::getInstance()->getTexture("CancelButton"), ResourceManager::getInstance()->getTexture("CancelButtonOver"));
        modelsSideWindow["1CancelButtonStructure"]->onClick = [this] () {onCancelClick();};

        //Parameter
        modelsSideWindow["1AddHeight"] = new Button ( 1050, 300, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1AddHeight"]->onClick = [this] () {updateHeightParameterAdd();};

        modelsSideWindow["1SoustracHeight"] = new Button (940, 300, 0, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1SoustracHeight"]->onClick = [this] () {updateHeightParameterMinus();};

        modelsSideWindow["1HeightLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Wall height", 945, 360, 0);


        SDL_itoa(height[0], buffer, 10);

        modelsSideWindow["1HeightNumber"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0}, buffer, 1005, 300, 0);


        modelsSideWindow["1AddStory"] = new Button ( 1220, 300, -1, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1AddStory"]->onClick = [this] () {updateStoryChosenPlus();};

        modelsSideWindow["1SoustracStory"] = new Button (1110, 300, -1, 50, 50, ResourceManager::getInstance()->getTexture("ChoixNonAppuyer"), ResourceManager::getInstance()->getTexture("ChoixAppuyer"));
        modelsSideWindow["1SoustracStory"]->onClick = [this] () {updateStoryChosenMinus();};

        modelsSideWindow["1StoryLabel"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial30")->getFont(), {128,128,128,0}, "Story Chosen", 1100, 360, 0);


        SDL_itoa(chosenStory, buffer, 10);
        modelsSideWindow["1StoryChosen"] = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0}, buffer, 1110 + 65, 300,0);



    }

    void updateStoryChosenPlus(){
        if(chosenStory < storyAmount)
            chosenStory++;
        if(chosenStory == height.size())
            height.push_back(1);

        SDL_itoa(chosenStory, buffer, 10);
        ((Label*)modelsSideWindow["1StoryChosen"])->updateTextTexture(buffer, ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0});

    }
    void updateStoryChosenMinus(){
        if(chosenStory)
            chosenStory--;
        SDL_itoa(chosenStory, buffer, 10);
        ((Label*)modelsSideWindow["1StoryChosen"])->updateTextTexture(buffer, ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0});

    }
    void updateHeightParameterAdd(){

            height.at(chosenStory)++;


        SDL_itoa(height[chosenStory], buffer, 10);
        ((Label*)modelsSideWindow["1HeightNumber"])->updateTextTexture(buffer, ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0});
    }

    void updateHeightParameterMinus(){

        if(height.at(chosenStory) > 1)
            height.at(chosenStory)--;
        SDL_itoa(height.at(chosenStory), buffer, 10);
        ((Label*)modelsSideWindow["1HeightNumber"])->updateTextTexture(buffer, ResourceManager::getInstance()->getResource<Font*>("font - arial28")->getFont(), {128,128,128,0});
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
    }

    void onWallClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        buildType = BUILD_WALL;

    }
    void onFloorClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        buildType = BUILD_FLOOR;
    }
    void onRoofClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        buildType = BUILD_ROOF;
    }
    void onCardboardClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = CARDBOARD;
    }
    void onWoodClick(){
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = WOOD;
    }
    void onRockClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = ROCK;
    }
    void onMetalClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        materialType = METAL;
    }
    void onSIMTiumClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        materialType = SIMTIUM;
    }
    unsigned int getHeight(){
        return height[0];
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
    unsigned int getFloorHeight(){
        if(chosenStory == 1)
            return height[0];
        unsigned int heightToReturn = 0;
        for(int i = 0; i < chosenStory; i++){
            heightToReturn += height[i];
        }
        return heightToReturn;
    }

};
unsigned int StructureWindow::chosenStory = 0;
unsigned int StructureWindow::storyAmount = 0;
#endif //STRUCTUREWINDOW_H
