/// \brief Menu moontrant les scores obtenus par différents joueurs
/// \details Interface accessible depuis le menu principal. Les scores sont stockés dans un fichier et classés en ordre décroissant.
/// \author Mathilde Harnois
/// \date 27 mars 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.
#ifndef SOURCE_HIGHSCORE_H
#define SOURCE_HIGHSCORE_H

#include "Menu.h"
#include "includes.h"

class Highscore : public Menu{
private:
    Button* backButton;
public:


    Highscore(){
        backButton = new Button (498, 550, 0.l, 284, 113, ResourceManager::getInstance()->getTexture("backButton"));
        backButton->onClick = [this]() {Scene::activeScene  = "MainMenu";};
    }


    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables) {
        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables) {
        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }

    void draw(){
        backButton->draw();
    }
};


#endif
