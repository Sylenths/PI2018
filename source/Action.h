
/// \brief Classe d'actions pouvant etre faites dans l'HUD
/// \details Classe abstraite qui sera parents de tout les types d'actions pouvant être fait par le joueur
/// \author Mickaël Grisé-Roy
/// \date 10 Avril 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.
#ifndef SOURCE_ACTION_H
#define SOURCE_ACTION_H
#define BUILD 0

#include "ActionParameter.h"

class Action {
protected:
    unsigned int actionType;///< Le type d'action

public:
    /// retourn le type d'action
    unsigned int getActionType(){
        return actionType;
    }
    virtual double getX(){}
    virtual double getY(){}
    virtual double getZj(){}
};

#endif //SOURCE_ACTION_H
