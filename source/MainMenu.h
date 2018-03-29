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

class MainMenu : public Menu {
private:
    Model* startButton;
    Model* settingsButton;
    Model* highscoreButton;
    Model* imageMenu;
    Model* wassup;

    void (*onClick)();
public:

    MainMenu(){


        startButton = new Button ( onClick, ResourceManager::getInstance()->getTexture("ButtonStart"), 967, 543, 0, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonStart", startButton);

        settingsButton = new Button( onClick, ResourceManager::getInstance()->getTexture("ButtonSettings"), 967, 363, 0, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonSettings", settingsButton);

        highscoreButton = new Button( onClick, ResourceManager::getInstance()->getTexture("ButtonHighScore"), 967, 363, 0, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonHighScore", highscoreButton);

        imageMenu = new Button( onClick, ResourceManager::getInstance()->getTexture("FondMaison"), 967, 363, 0, 298, 128);
        ResourceManager::getInstance()->addResource("FondMaison", imageMenu);






    }

    void loadMenu(){
        /*ProjetFinal::observables[SDL_MOUSEBUTTONDOWN]->subscribe(startButtom);
        ProjetFinal::observables[SDL_MOUSEBUTTONDOWN]->subscribe(settingButtom);
        ProjetFinal::observables[SDL_MOUSEBUTTONDOWN]->subscribe(highscoreButtom);*/
    }

    void draw(){
        startButton->draw();
        settingsButton->draw();
        highscoreButton->draw();
        imageMenu->draw();
    }


};


#endif
