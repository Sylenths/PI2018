/// \brief Représentation d'une fenêtre de coté pour le InGameOverlay
/// \details classe abstraite représentant une fenêtre de coté.
/// \author Guillaume Julien - Desmarchais
/// \date 20 mars 2018
/// \version 0.1
/// \warning Aucun
/// \bug Aucun
#ifndef SIDEWINDOW_H
#define SIDEWINDOW_H
class SideWindow{
protected:
    unsigned int windowType;

public:

    unsigned int getWindowType(){
            return windowType;
    }

    virtual void draw(){}

    virtual void deleteTexture(){}

};

#endif //SIDEWINDOW_H
