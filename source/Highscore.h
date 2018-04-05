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

#define TAILLE_MAX 50

class Highscore : public Menu{
private:
    Button* backButtonHighscore;
    Scores* scores[12];

    std::string fichierSauvegardeScores;


public:
    void loadScores(){
       FILE* fichier = fopen("../../SauvegardeScores.txt","r");
        char charBuffer[TAILLE_MAX];
        std::string buffer;
        std::string name;
        std::string scoreFichier;
        int j = 0;
        if(fichier){
            for (int i = 0; i <10 ; ++i) {
                fgets(charBuffer,TAILLE_MAX,fichier);
                buffer = charBuffer;

                 while (buffer[j] != ' ') {
                     name = name + buffer[j];
                     j++;
                 }
                 j += 2;
                 while (buffer[j] != ' ') {
                   scoreFichier = scoreFichier + buffer[j];
                     j++;
                 }
                int score = std::stoi(scoreFichier);
                scores[i]->setScore(name,score);
                j = 0;
                name = "";
                scoreFichier = "";


            }

            fclose(fichier);
        }
        //TODO Trier le tableau.

    }



    Highscore(){
        backButtonHighscore = new Button (498, 550, 0.l, 284, 113, ResourceManager::getInstance()->getTexture("backButton"),ResourceManager::getInstance()->getTexture("BackButtonOver"));
        ResourceManager::getInstance()->addResource("backButtonHighscore", backButtonHighscore);
        backButtonHighscore->onClick = [this]() {Scene::activeScene  = "MainMenu";};

        for (int i = 0; i < 10 ; ++i) {
            scores[i] = new Scores();
        }
    }

    ~Highscore() {
        for (int i = 0; i <10 ; ++i) {
            delete scores[i];
        }
    }

    void updateScore(std::string name, unsigned int score){
        Scores* toCompare = new Scores;
        toCompare->setScore(name, score);
        scores[11] = toCompare;

        // TODO Trier le tableau

        delete scores[11];
    }

    void save(){
        FILE* fichier = fopen("../../SauvegardeScores.txt","w");
        if(fichier){
            for (int i = 0; i <10 ; ++i) {
                const char* name = scores[i]->getName().c_str();
                char score[10];
                SDL_itoa(scores[i]->getScore(),score,10);
                fprintf(fichier,name);
                fprintf(fichier, "  ");
                fprintf(fichier,score);
                fprintf(fichier, " ");
                fprintf(fichier,"\n");

            }

            fclose(fichier);
        }


    }



    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables) {

        if(!(*observables)[SDL_MOUSEBUTTONDOWN])
            (*observables)[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>;
        if(!(*observables)[SDL_MOUSEMOTION])
            (*observables)[SDL_MOUSEMOTION]= new Observable<SDL_Event*>;

        (*observables)[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButtonHighscore"));
        (*observables)[SDL_MOUSEMOTION]->subscribe(ResourceManager::getInstance()->getResource<Button*>("backButtonHighscore"));
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>* observables) {
        (*observables)[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButtonHighscore"));
        (*observables)[SDL_MOUSEMOTION]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("backButtonHighscore"));
    }

    void draw(){
        backButtonHighscore->draw();
    }
};


#endif
