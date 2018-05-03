/// \brief Gère les entrées utilisateur
/// \author Shelby Versailles, Tai Chen Li
/// \date 12 Avril 2018
/// \version 0.1
#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <SDL2/SDL_events.h>
#include "Observer.h"



class Controller : public Observer<SDL_Event*>{
private:
    int keyDown;
    int keyUp;
    int mouseMotion[2];
    int mouseClickPosition[3];
public:
    ///Constructeur
    Controller(){
        keyDown = 0;
        keyUp = 0;
        mouseClickPosition[2] = -1;
    }

    void notify(SDL_Event* event){
	    switch(event->type){
		    case SDL_KEYDOWN:
			    keyDown = event->key.keysym.sym;
			    keyUp = 0;
			    break;
		    case SDL_KEYUP:
			    keyUp = event->key.keysym.sym;
			    keyDown = 0;
			    break;
		    case SDL_MOUSEMOTION:
			    mouseMotion[0] = event->motion.xrel;
			    mouseMotion[1] = event->motion.yrel;
			    break;
		    case SDL_MOUSEBUTTONDOWN:
			    mouseClickPosition[0] = event->button.x;
			    mouseClickPosition[1] = event->button.y;
			    mouseClickPosition[2] = event->button.button;
			    break;
		    case SDL_MOUSEBUTTONUP:
			    mouseClickPosition[0] = event->button.x;
			    mouseClickPosition[1] = event->button.y;
			    //mouseClickPosition[2] = event->button.button;
			    break;
		    default:
			    break;
	    }
    }
/// retourne la touche qui a été appuillée
/// \return touche apuillée
    int getKeyDown(){
        return keyDown;
    }
/// retourne la touche qui a été relachée
/// \return touche relacher
    int getKeyUp(){
        return keyUp;
    }
/// retourne le deplacement relatif de la souris
/// \return deplacement xrel, deplacement yrel
    int* getMouseMotion(){
        return mouseMotion;
    }
/// retourne Ou la souris etait quand il y a eu un clic
/// \return positionX, positionY, Click
    int* getClickMousePosition(){
        return mouseClickPosition;
    }
/// Remets mouseMotion a 0,0
    void resetMouseMotion(){
        mouseMotion[0] = 0;
        mouseMotion[1] = 0;
    }
    void resetClicMousePosition(){
        mouseClickPosition[0] = 0;
        mouseClickPosition[1] = 0;
        mouseClickPosition[2] = -1;
    }

    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables, Controller* controller){
        ///Souris
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(controller);
        if (!observables[SDL_MOUSEBUTTONUP]) observables[SDL_MOUSEBUTTONUP] = new Observable<SDL_Event*>();
        observables[SDL_MOUSEBUTTONUP]->subscribe(controller);
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();
        observables[SDL_MOUSEMOTION]->subscribe(controller);
        ///Clavier
        if (!observables[SDL_KEYDOWN]) observables[SDL_KEYDOWN] = new Observable<SDL_Event*>();
        observables[SDL_KEYDOWN]->subscribe(controller);
        if (!observables[SDL_KEYUP]) observables[SDL_KEYUP] = new Observable<SDL_Event*>();
        observables[SDL_KEYUP]->subscribe(controller);
    }
};



#endif
