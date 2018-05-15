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
        modelsSideWindow["SideMenuStructure"] = new Image("SideMenuStructure", 920, 0, 0, 360, 720, EntityManager::get<Texture2d*>("StructureWindow")->ID);


        //type de structure
        modelsSideWindow["1FondationIcon"] = new CheckBox ("1FondationIcon", 970, 90, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1FondationIcon"]->onClick = [this] () { onFoundationClick();};
        modelsSideWindow["1FondationLabel"] = new Label("1FondationLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Fondation", 963, 150, 0);
        modelsSideWindow["1FondationDesc"] = new TextWindow("1FondationDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure de base pour permettre de construire les autres types de structure ou de machines.", 1110, 440, 0, 135, 300, modelsSideWindow["1FondationIcon"]);

        modelsSideWindow["1MurIcon"] = new CheckBox ("1MurIcon", 1040, 90, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1MurIcon"]->onClick = [this] () { onWallClick();};
        modelsSideWindow["1MurLabel"] = new Label("1MurLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Mur", 1050, 150, 0);
        modelsSideWindow["1MurDesc"] = new TextWindow("1MurDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure permet de construire des murs sur tous les fondations, il faut rentrer une hauteur en parametre.", 1110, 440, 0, 135, 300, modelsSideWindow["1MurIcon"]);

        modelsSideWindow["1PlancherIcon"] = new CheckBox ("1PlancherIcon", 1110, 90, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1PlancherIcon"]->onClick = [this] () {onFloorClick();};
        modelsSideWindow["1PlanLabel"] = new Label("1PlanLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Plancher", 1105, 150, 0);
        modelsSideWindow["1PlancherDesc"] = new TextWindow("1PlancherDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure permet de construire des planchers sur des fondations possedant des murs, il faut rentrer l'etage sur lequel on veut travailler.", 1110, 440, 0, 135, 300, modelsSideWindow["1PlancherIcon"]);

        modelsSideWindow["1ToitIcon"] = new CheckBox ("1ToitIcon", 1180, 90, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1ToitIcon"]->onClick = [this] () {onRoofClick();};
        modelsSideWindow["1ToitLabel"] = new Label("1ToitLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Toit", 1190, 150, 0);
        modelsSideWindow["1ToitDesc"] = new TextWindow("1ToitDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "La structure permet de construire un toit sur des fondations possedant des murs.", 1110, 440, 0, 135, 300, modelsSideWindow["1ToitIcon"]);

        //type de matérieux
        modelsSideWindow["1CartonIcon"] = new CheckBox ("1CartonIcon", 940, 205, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1CartonIcon"]->onClick = [this] () {onCardboardClick();};
        modelsSideWindow["1CartonLabel"] = new Label("1CartonLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Carton", 940, 265, 0);
        modelsSideWindow["1CartonLabelDesc"] = new TextWindow("1CartonLabelDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::carton->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1CartonIcon"]);

        modelsSideWindow["1BoisIcon"] = new CheckBox ("1BoisIcon", 1010, 205, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1BoisIcon"]->onClick = [this] () {onWoodClick();};
        modelsSideWindow["1BoisLabel"] = new Label("1BoisLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Bois", 1010, 265, 0);
        modelsSideWindow["1BoisDesc"] = new TextWindow("1BoisDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::bois->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1BoisIcon"]);

        modelsSideWindow["1PierreIcon"] = new CheckBox ("1PierreIcon", 1080, 205, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1PierreIcon"]->onClick = [this] () {onRockClick();};
        modelsSideWindow["1PierreLabel"] = new Label("1PierreLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Pierre", 1080, 265, 0);
        modelsSideWindow["1PierreDesc"] = new TextWindow("1PierreDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::pierre->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1PierreIcon"]);

        modelsSideWindow["1MetalIcon"] = new CheckBox ("1MetalIcon", 1150, 205, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1MetalIcon"]->onClick = [this] () {onMetalClick();};
        modelsSideWindow["1MetalLabel"] = new Label("1MetalLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Metal", 1150, 265, 0);
        modelsSideWindow["1MetalDesc"] = new TextWindow("1MetalDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::metal->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1MetalIcon"]);

        modelsSideWindow["1SIMTiumIcon"] = new CheckBox ("1SIMTiumIcon", 1220, 205, 0, 50, 50, EntityManager::get<Texture2d*>("ChoixNonAppuyer")->ID, EntityManager::get<Texture2d*>("ChoixAppuyer")->ID);
        modelsSideWindow["1SIMTiumIcon"]->onClick = [this] () {onSIMTiumClick();};
        modelsSideWindow["1SIMTiumLabel"] = new Label("1SIMTiumLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "SIMTium", 1220, 265, 0);
        modelsSideWindow["1SIMTiumDesc"] = new TextWindow("1SIMTiumDesc", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, Materiel::simtium->getDescription() , 940, 440, 0, 150, 300, modelsSideWindow["1SIMTiumIcon"]);

        //Building Button
        modelsSideWindow["1BuildingButtonStructure"] = new Button ("1BuildingButtonStructure", 930, 580, 0, 340, 60, EntityManager::get<Texture2d*>("BuildButton")->ID, EntityManager::get<Texture2d*>("BuildButtonOver")->ID);
        modelsSideWindow["1BuildingButtonStructure"]->onClick = [this] () {onBuildClick();};

        modelsSideWindow["1CancelButtonStructure"] = new Button ("1CancelButtonStructure", 930, 650, 0, 340, 60, EntityManager::get<Texture2d*>("CancelButton")->ID, EntityManager::get<Texture2d*>("CancelButtonOver")->ID);
        modelsSideWindow["1CancelButtonStructure"]->onClick = [this] () {onCancelClick();};

        //Parameter
        modelsSideWindow["1AddHeight"] = new Button ("1AddHeight", 1150, 300, 0, 20, 20, EntityManager::get<Texture2d*>("PlusButton")->ID);
        modelsSideWindow["1AddHeight"]->onClick = [this] () {updateHeightParameterAdd();};

        modelsSideWindow["1SoustracHeight"] = new Button ("1SoustracHeight", 1050, 300, 0, 20, 20, EntityManager::get<Texture2d*>("MoinsButton")->ID);
        modelsSideWindow["1SoustracHeight"]->onClick = [this] () {updateHeightParameterMinus();};

        modelsSideWindow["1HeightLabel"] = new Label("1HeightLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Wall height : ", 925, 300, 0);


        SDL_itoa(height[0], buffer, 10);

        modelsSideWindow["1HeightNumber"] = new Label("1HeightNumber", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, buffer, 1100, 300, 0);


        modelsSideWindow["1AddStory"] = new Button ("1AddStory", 1150, 335, 0, 20, 20, EntityManager::get<Texture2d*>("PlusButton")->ID);
        modelsSideWindow["1AddStory"]->onClick = [this] () {updateStoryChosenPlus();};

        modelsSideWindow["1SoustracStory"] = new Button ("1SoustracStory", 1050, 335, 0, 20 ,20, EntityManager::get<Texture2d*>("MoinsButton")->ID);
        modelsSideWindow["1SoustracStory"]->onClick = [this] () {updateStoryChosenMinus();};

        modelsSideWindow["1StoryLabel"] = new Label("1StoryLabel", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, "Story Chosen : ", 925, 335, 0);


        SDL_itoa(chosenStory, buffer, 10);
        modelsSideWindow["1StoryChosen"] = new Label("1StoryChosen", EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0}, buffer, 1100, 335 , 0);
    }

    void updateStoryChosenPlus(){
        if(chosenStory < storyAmount)
            chosenStory++;
        if(chosenStory == height.size())
            height.push_back(1);

        SDL_itoa(chosenStory, buffer, 10);
        ((Label*)modelsSideWindow["1StoryChosen"])->updateTextTexture(buffer, EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0});

    }
    void updateStoryChosenMinus(){
        if(chosenStory)
            chosenStory--;
        SDL_itoa(chosenStory, buffer, 10);
        ((Label*)modelsSideWindow["1StoryChosen"])->updateTextTexture(buffer, EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0});

    }
    void updateHeightParameterAdd(){

            height.at(chosenStory)++;


        SDL_itoa(height[chosenStory], buffer, 10);
        ((Label*)modelsSideWindow["1HeightNumber"])->updateTextTexture(buffer, EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0});
    }

    void updateHeightParameterMinus(){

        if(height.at(chosenStory) > 1)
            height.at(chosenStory)--;
        SDL_itoa(height.at(chosenStory), buffer, 10);
        ((Label*)modelsSideWindow["1HeightNumber"])->updateTextTexture(buffer, EntityManager::get<Font*>("font - arial32")->getFont(), {128,128,128,0});
    }

    void onBuildClick(){
        if(buildType == BUILD_FONDATION ||(buildType != BUILD_NOTHING && materialType)) {
            isBuilding = true;
            closed = true;
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
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->check();
        buildType = BUILD_FONDATION;
    }

    void onWallClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->check();
        buildType = BUILD_WALL;

    }
    void onFloorClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->check();
        buildType = BUILD_FLOOR;
    }
    void onRoofClick(){
        ((CheckBox*)modelsSideWindow["1FondationIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MurIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PlancherIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1ToitIcon"])->check();
        buildType = BUILD_ROOF;
    }
    void onCardboardClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->check();
        materialType = CARDBOARD;
    }
    void onWoodClick(){
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->check();
        materialType = WOOD;
    }
    void onRockClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->check();
        materialType = ROCK;
    }
    void onMetalClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->check();
        materialType = METAL;
    }
    void onSIMTiumClick(){
        ((CheckBox*)modelsSideWindow["1BoisIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1CartonIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1PierreIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1MetalIcon"])->uncheck();
        ((CheckBox*)modelsSideWindow["1SIMTiumIcon"])->check();
        materialType = SIMTIUM;
    }
    unsigned int getHeight(){
        return height[chosenStory];
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
