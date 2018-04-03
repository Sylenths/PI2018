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

class Settings : public Menu{
private:
    Button * FPSButton, * backButton;
    Label* resolution, * showFPS;
    Image2D* fond;
    Font* font = ResourceManager::getInstance()->getResource<Font*>("font - arial12");

public:
    Settings() {

        fond = new Image2D (ResourceManager::getInstance()->getTexture("FondSettings"), 0, 0, 0, 1280, 720);
        ResourceManager::getInstance()->addResource("FondSettings", fond);

        FPSButton = new Button (  ResourceManager::getInstance()->getTexture("FPSButton"), 712, 300, 0.2, 510, 113);
        ResourceManager::getInstance()->addResource("FPSButton", FPSButton);

        backButton = new Button (  ResourceManager::getInstance()->getTexture("backButton"), 498, 550, 0.l, 284, 113);
        ResourceManager::getInstance()->addResource("backButton", backButton);
        backButton->onClick = [this]() {Menu::activeMenu = "MainMenu";};

        showFPS = new Label(font->getFont(), {128,128,128,0}, "Show FPS : ", 71, 300, 0.1, 466, 113);
    }

    void draw (){
        showFPS->draw();
        FPSButton->draw();
        backButton->draw();
        fond->draw();
    }

    void unsubscirbe(){

    }

    void subscribe(){
        
    }
};


#endif


