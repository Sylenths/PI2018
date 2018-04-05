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
#include "Scores.h"
#include <iostream>
#include <fstream>
#include <cstdio>

class Highscore : public Menu{
private:
    Button* backButton;
    Scores* scores[11];
    std::string fichierSauvegardeScores;


public:


    Highscore(){
       // FILE * fichier;
        //fichierSauvegardeScores = "../../fichierScores.txt";

        backButton = new Button (498, 550, 0.l, 284, 113, ResourceManager::getInstance()->getTexture("backButton"),ResourceManager::getInstance()->getTexture("BackButtonOver"));
        ResourceManager::getInstance()->addResource("backButton", backButton);
        backButton->onClick = [this]() {Scene::activeScene  = "MainMenu";};




    }


    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables) {

        if(!(*observables)[SDL_MOUSEBUTTONDOWN])
            (*observables)[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>;
        if(!(*observables)[SDL_MOUSEMOTION])
            (*observables)[SDL_MOUSEMOTION]= new Observable<SDL_Event*>;

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables) {
        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButton"));
    }

    void draw(){
        backButton->draw();
    }
};


#endif
