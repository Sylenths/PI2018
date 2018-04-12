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
};



#endif
