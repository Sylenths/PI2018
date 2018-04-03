/// \brief Représentation du menu des options du jeu.
/// \details Interface permettant de modifier quelques options de jouabilité.
/// \author Antoine Legault, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SOURCE_SETTINGS_H
#define SOURCE_SETTINGS_H

#include "includes.h"
#include "Label.h"
#include "Font.h"

class Settings : public Menu{
private:
    Button* leftArrowButton, * rightArrowButton, * FPSButton, * backButton;
    Label* resolution, * showFPS;
    //Font* font = ResourceManager::getInstance()->getResource<Font*>("font - arial12");

public:
    Settings() {
        leftArrowButton = new Button ( ResourceManager::getInstance()->getTexture("ButtonLeftArrow"), 723, 299, 0.1, 51, 51);
        ResourceManager::getInstance()->addResource("ButtonLeftArrow", leftArrowButton);

        rightArrowButton = new Button ( ResourceManager::getInstance()->getTexture("ButtonRightArrow"), 1160, 299, 0.1, 51, 51);
        ResourceManager::getInstance()->addResource("ButtonRightArrow", rightArrowButton);

        FPSButton = new Button (  ResourceManager::getInstance()->getTexture("ButtonFPS"), 712, 439, 0.2, 510, 113);
        ResourceManager::getInstance()->addResource("ButtonFPS", FPSButton);
        //FPSButton->setOnClick(std::bind(&ProjetFinal::setShowFPS, FPSButton));

        backButton = new Button (  ResourceManager::getInstance()->getTexture("ButtonBack"), 498, 704, 0.l, 284, 113);
        ResourceManager::getInstance()->addResource("ButtonBack", backButton);
        backButton->onClick = [this]() {Menu::activeMenu = "MainMenu";};

        //resolution = new Label(font->getFont(), {128, 128, 128, 0}, "Resolution : ", 71, 330, 0.1,  466, 113);
        //showFPS = new Label(font->getFont(), {128,128,128,0}, "Show FPS : ", 71, 443, 0.1, 466, 113);
    }

    void draw (){
        leftArrowButton->draw();
        rightArrowButton->draw();
        FPSButton->draw();
        backButton->draw();
    }
};


#endif


