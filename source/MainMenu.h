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

class MainMenu : public Menu {
private:
    Model* startButtom;
    Model* settingButtom;
    Model* highscoreButtom;
    Model* imageMenu;

    void (*onClick)();
public:

    MainMenu(){
        startButtom = new Button ( onClick,"start.png", 967, 543, 0, 298, 128);
        settingButtom = new Button( onClick, "settings.png", 967, 363, 0, 298, 128);
        highscoreButtom = new Button( onClick, "highscore.png", 967, 178, 0, 298, 128);
        imageMenu = new Image2D("maisonApp.png", 0, 720, 0, 1280, 720);
    }

    void loadMenu(){
        

    }


};


#endif
