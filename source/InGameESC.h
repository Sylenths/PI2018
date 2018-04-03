
#ifndef SOURCE_INGAMEESC_H
#define SOURCE_INGAMEESC_H

#include "Menu.h"

class InGameESC : public Menu{
public:
    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*> observables) {

    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*> observables) {

    }

    void draw (){

    }
};


#endif
