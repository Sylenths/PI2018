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
    Button * FPSButton, * backButton;
    Label * showFPS;
    Image* fond;
    Font* font = ResourceManager::getInstance()->getResource<Font*>("font - arial12");

public:
    Settings() {

        fond = new Image (ResourceManager::getInstance()->getTexture("FondSettings"), 0, 0, 0.1, 1280, 720);
        ResourceManager::getInstance()->addResource("FondSettings", fond);

        FPSButton = new Button (712, 300, 0.2, 510, 113, ResourceManager::getInstance()->getTexture("FPSButtonNO"), ResourceManager::getInstance()->getTexture("FPSButtonNOOVER"));
        ResourceManager::getInstance()->addResource("FPSButtonNO", FPSButton);
        FPSButton->onClick = [this]() {FPSOnOff();};

        backButton = new Button (498, 550, 0.l, 284, 113, ResourceManager::getInstance()->getTexture("backButton"), ResourceManager::getInstance()->getTexture("BackButtonOver"));
        ResourceManager::getInstance()->addResource("backButton", backButton);
        backButton->onClick = [this]() {Scene::activeScene  = "MainMenu";};

        showFPS = new Label(font->getFont(), {128,128,128,0}, "Show FPS : ", 71, 300, 0.1, 466, 113);

    }

    ~Settings(){
        delete fond;
        delete FPSButton;
        delete backButton;
        delete showFPS;
        delete font;
    }


    void FPSOnOff(){

    }

    void draw (){
        showFPS->draw();
        FPSButton->draw();
        backButton->draw();
        fond->draw();


    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables){
        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));


        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }

    void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>* observables){
        if(!(*observables)[SDL_MOUSEBUTTONDOWN])
            (*observables)[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>;
        if(!(*observables)[SDL_MOUSEMOTION])
            (*observables)[SDL_MOUSEMOTION]= new Observable<SDL_Event*>;

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("FPSButtonNO"));

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }
};


#endif


