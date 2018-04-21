/// \brief Représentation de la fenêtre de construction des structures
/// \details Active le mode destruction.
/// \author Guillaume Julien - Desmarchais
/// \date 20 mars 2018
/// \version 0.1
/// \warning (Delete Mode On) ne prend pas de e à mode.
/// \bug Aucun
#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include "SideWindow.h"
#include "includes.h"
class DeleteWindow : public SideWindow{

private:
    Image* logoDestruction;

public:

    DeleteWindow(){
        logoDestruction = new Image(700, 0, 0.1, 260, 60, ResourceManager::getInstance()->getTexture("deletewindow"));
        windowType = 5;
    }

    void draw(){
        logoDestruction->draw();
    }

    void deleteTexture(){
        delete(logoDestruction);
    }
};
#endif //DELETEWINDOW_H
