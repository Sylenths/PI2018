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
    void ScrollDown(){
        if (position + nombreDeBoutonsAffiche < boutons.size()){
            scrollDown = true;
            position += nombreDeBoutonsAffiche;

            //boutons[position]->updateButtonPosition(920,50,0);
            //boutons[position + 1]->updateButtonPosition(920,130,0);
            //boutons[position + 2]->updateButtonPosition(920,210,0);

        }
    }
//Retourne la postition avant le scroll.
    void ScrollUp(){
        if(position > 0){
            scrollUp = true;
            position -= nombreDeBoutonsAffiche;
        }

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
        return scrollDown;
    }
    int getPosition(){
        return position;
    }

    void draw(){
        for (int i = 0; i <nombreDeBoutonsAffiche ; ++i) {
            if(boutons[position + i])
            boutons[position+i]->draw();
        }
    }



};


#endif
