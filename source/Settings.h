/// \brief Représentation du menu des options du jeu.
/// \details Interface permettant de modifier quelques options de jouabilité.
/// \author Antoine Legault, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.1
/// \warning Les boutons restent en fonction, mais ils sont invisibles.
/// \bug Aucun.

#ifndef SOURCE_SETTINGS_H
#define SOURCE_SETTINGS_H

#include "includes.h"
#include "Label.h"
#include "Font.h"
#include "Observable.h"

class Settings : public Menu{
private:
    Button * FPSButtonNO, * backButton, * FPSButtonYES;
    Label * showFPS;
    Image* fond;
    Font* font = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
    bool FpsOnOff;

public:
    Settings() {

        fond = new Image (0, 0, 0, 1280, 720, ResourceManager::getInstance()->getTexture("FondSettings"));
        ResourceManager::getInstance()->addResource("FondSettings", fond);

        FPSButtonNO = new Button (712, 300, 0, 510, 113, ResourceManager::getInstance()->getTexture("FPSButtonNO"), ResourceManager::getInstance()->getTexture("FPSButtonNOOVER"));
        ResourceManager::getInstance()->addResource("FPSButtonNO", FPSButtonNO);
        FPSButtonNO->onClick = [this]() {FPSOnOff();};

        FPSButtonYES = new Button(712, 300, 0, 510, 113, ResourceManager::getInstance()->getTexture("FPSButtonYES"), ResourceManager::getInstance()->getTexture("FPSButtonYESOVER"));
        ResourceManager::getInstance()->addResource("FPSButtonYES", FPSButtonYES);
        FPSButtonYES->onClick = [this]() {FPSOnOff();};

        backButton = new Button (498, 550, 0.l, 284, 113, ResourceManager::getInstance()->getTexture("backButton"), ResourceManager::getInstance()->getTexture("BackButtonOver"));
        ResourceManager::getInstance()->addResource("backButton", backButton);
        backButton->onClick = [this]() {Scene::activeScene  = "MainMenu";};

        showFPS = new Label(font->getFont(), {128,128,128,0}, "Show FPS : ", 71, 300, 0.1, 466, 113);
        FpsOnOff = false;

    }

    ~Settings(){
        delete fond;
        delete FPSButtonNO;
        delete backButton;
        delete showFPS;
        delete font;
        delete FPSButtonYES;
    }


    void FPSOnOff(){
        if(FpsOnOff == true){
            FpsOnOff = false;
        } else{
            FpsOnOff = true;
        }
    }

    void draw (){
        showFPS->draw();
        if(FpsOnOff == true){
            FPSButtonYES->draw();
        }
        if(FpsOnOff == false){
            FPSButtonNO->draw();
        }
        backButton->draw();
        fond->draw();



    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables){
        if(FpsOnOff == true){
            (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonYES"));
            (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonYES"));
        }
        if(FpsOnOff == false){
            (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));
            (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));
        }

        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }

    void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>* observables){
        if(!(*observables)[SDL_MOUSEBUTTONDOWN])
            (*observables)[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>;
        if(!(*observables)[SDL_MOUSEMOTION])
            (*observables)[SDL_MOUSEMOTION]= new Observable<SDL_Event*>;

        if(FpsOnOff == true){
            (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonYES"));
            (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonYES"));
        }
        if(FpsOnOff == false){
            (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));
            (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));
        }

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }
};


#endif


