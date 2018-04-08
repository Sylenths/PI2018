
#ifndef SOURCE_INGAMEESC_H
#define SOURCE_INGAMEESC_H

class InGameESC : public Menu {
public:
    void draw() { }
    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) {}
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) {}
};


#endif
