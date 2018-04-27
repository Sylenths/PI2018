#ifndef SOURCE_SCROLLINGMENU_H
#define SOURCE_SCROLLINGMENU_H

#include "includes.h"

class ScrollingMenu {
private:
    std::map<unsigned int, Button*>  boutons;
    int position;
    int nombreDeBoutonsAffiche;
    bool scrollDown;
    bool scrollUp;
public:
    ScrollingMenu(std::map<unsigned int, Button*>  boutons, int nombreDeBoutonsAffiche){
        int size = boutons.size();
        for (int i = 0; i < boutons.size() ; ++i) {
            this->boutons[i] = boutons[i];
        }
        position = 0;
        this->nombreDeBoutonsAffiche = nombreDeBoutonsAffiche;
        scrollDown = false;
        scrollUp = false;
    }
// Retourne la position avant le scroll.
    int ScrollDown(){
        if (position + nombreDeBoutonsAffiche < boutons.size()){
            scrollDown = true;
            position++;
        }
        return (position - 1);
    }
//Retourne la postition avant le scroll.
    int ScrollUp(){
        if(position - 1 > 0){
            scrollUp = true;
            position--;
        }
        return (position + 1);
    }

    void resetScrollUp(){
        scrollUp = false;
    }
    void resetScrollDown(){
    scrollDown = false;
    }

    bool getScrollUp(){
        return scrollUp;
    }
    bool getScrollDown(){
        return ScrollDown();
    }

    void draw(){
        for (int i = 0; i <nombreDeBoutonsAffiche ; ++i) {
            boutons[position + i]->draw();
        }
    }



};


#endif
