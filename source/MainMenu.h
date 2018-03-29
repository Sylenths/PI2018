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
#include "onClickFunctionsPart1.h"
#include "onClickFunctionsPart2.h"


class MainMenu : public Menu {
private:
    Model* startButton;         ///< Bouton pour commencer la partie.
    Model* settingsButton;      ///< Bouton pour accéder au settings.
    Model* highscoreButton;     ///< Bouton pour accéder au tableau des highscores.
    Model* imageMenu;           ///< Image principal du menu.

    void (*onClickStart)();
    void (*onClickHighscore)();
    void (*onClickSettings)();
public:


    /// Constructeur
    MainMenu(){


        imageMenu = new Image2D( ResourceManager::getInstance()->getTexture("FondMaison"), 0, 0, 0, 1280, 720);
        ResourceManager::getInstance()->addResource("FondMaison", imageMenu);

        startButton = new Button ( onClickStart, ResourceManager::getInstance()->getTexture("ButtonStart"), 967, 75, 0, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonStart", startButton);

        settingsButton = new Button( onClickSettings, ResourceManager::getInstance()->getTexture("ButtonSettings"), 967, 275, 0, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonSettings", settingsButton);

        highscoreButton = new Button( onClickHighscore, ResourceManager::getInstance()->getTexture("ButtonHighScore"), 967, 475, 0, 298, 128);
        ResourceManager::getInstance()->addResource("ButtonHighScore", highscoreButton);

        onClickHighscore = nullptr;
        onClickSettings = nullptr;
        onClickStart = nullptr;


    }

    void draw(){

        startButton->draw();
        settingsButton->draw();
        highscoreButton->draw();
        imageMenu->draw();
    }


};


#endif
