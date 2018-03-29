/// \brief Représentation du menu principal en jeu.
/// \details Interface qui apparait lorsqu'on ouvre le jeu.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_MAINMENU_H
#define SOURCE_MAINMENU_H

#include "Menu.h"
#include "Model.h"
#include "Button.h"
#include "Image2D.h"
#include "ProjetFinal.h"
#include "ResourceManager.h"
#include "Label.h"

class MainMenu : public Menu {
private:
    Model* startButton;
    Model* settingsButton;
    Model* highscoreButton;
    Model* imageMenu;
    Model* testLabel;


public:

    MainMenu(){


        imageMenu = new Image2D( ResourceManager::getInstance()->getTexture("FondMaison"), 0, 0, 0.8, 1280, 720);
        ResourceManager::getInstance()->addResource("FondMaison", imageMenu);

        startButton = new Button ( ResourceManager::getInstance()->getTexture("ButtonStart"), 967, 75, 0.3, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonStart", startButton);

        settingsButton = new Button( ResourceManager::getInstance()->getTexture("ButtonSettings"), 967, 275, 0.2, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonSettings", settingsButton);

        highscoreButton = new Button(  ResourceManager::getInstance()->getTexture("ButtonHighScore"), 967, 475, 0.1, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonHighScore", highscoreButton);

        testLabel = new Label(ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(),{255,255,255,255},"test",50,50,0.7,140,140);
        ((Label*) testLabel)->updateTextTexture("test2.0",ResourceManager::getInstance()->getResource<Font*>("font - arial12")->getFont(),{255,255,255,255});


    }

    void loadMenu(){
        /*ProjetFinal::observables[SDL_MOUSEBUTTONDOWN]->subscribe(startButtom);
        ProjetFinal::observables[SDL_MOUSEBUTTONDOWN]->subscribe(settingButtom);
        ProjetFinal::observables[SDL_MOUSEBUTTONDOWN]->subscribe(highscoreButtom);
         */
    }

    void draw(){
        testLabel->draw();
        imageMenu->draw();
        startButton->draw();
        settingsButton->draw();
        highscoreButton->draw();

    }


};


#endif
