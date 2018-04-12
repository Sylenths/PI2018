/// \brief
/// \details
/// \author Shelby Versailles
/// \date 12 Avril 2018
/// \version 0.1
#ifndef CONTROLER_H
#define CONTROLER_H


#include <SDL2/SDL_events.h>
#include "Observer.h"



class Controler : public Observer<SDL_Event*>{
private:
    int keyDown;
    int keyUp;
    int mouseMotion[2];
    int mouseClickPosition[3];
public:
    ///Constructeur
    Controler(){
        keyDown = NULL;
        keyUp = NULL;
    }

    void notify(SDL_Event* event){
        if(event->type == SDL_KEYDOWN){
            keyDown = event->key.keysym.sym;
        }
        if(event->type == SDL_KEYUP){
            keyUp = event->key.keysym.sym;
            keyDown = NULL;
        }
        if(event->type == SDL_MOUSEMOTION){
            mouseMotion[0] = event->motion.xrel;
            mouseMotion[1] = event->motion.yrel;
        }
        if(event->type == SDL_MOUSEBUTTONDOWN){
            mouseMotion[0] = event->motion.xrel;
            mouseMotion[1] = event->motion.yrel;
        }
        if(event->type == SDL_MOUSEBUTTONDOWN){
            mouseClickPosition[0] = event->button.x;
            mouseClickPosition[1] = event->button.y;
            mouseClickPosition[2] = event->button.button;
        }
    }

    int getKeyDown(){
        return keyDown;
    }
    int getKeyUp(){
        return keyUp;
    }
    int* getMouseMotion(){
        return mouseMotion;
    }
    int* getClickMousePosition(){
        return mouseClickPosition;
    }
    void resetMouseMotion(){
        mouseMotion[0] = 0;
        mouseMotion[1] = 0;
    }

    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables, Controler* controler){
        ///Souris
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(controler);
        if (!observables[SDL_MOUSEBUTTONUP]) observables[SDL_MOUSEBUTTONUP] = new Observable<SDL_Event*>();
        observables[SDL_MOUSEBUTTONUP]->subscribe(controler);
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();
        observables[SDL_MOUSEMOTION]->subscribe(controler);
        ///Clavier
        if (!observables[SDL_KEYDOWN]) observables[SDL_KEYDOWN] = new Observable<SDL_Event*>();
        observables[SDL_KEYDOWN]->subscribe(controler);
        if (!observables[SDL_KEYUP]) observables[SDL_KEYUP] = new Observable<SDL_Event*>();
        observables[SDL_KEYUP]->subscribe(controler);
    }
};



#endif
