/// \brief Classe de parametre
/// \details Classe qui contient un double
/// \author Mickaël Grisé-Roy
/// \date 10 Avril 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SOURCE_ACTIONINT_H
#define SOURCE_ACTIONINT_H

#include "ActionParameter.h"

class ActionInt : public ActionParameter{
private:
    int data;///< La donnée du parametre


public:
    ///Constructeur
    /// \param name nom du param dans la map qui sera returned
    /// \param data La data
    ActionInt(std::string name, int data) : ActionParameter(name) {
        this->data = data;
    }
    /// Retourne le tyoe d'action

    int getType() {
        return SIMINT;
    }

    /// retourne la data

    int getData(){
        return data;
    }

};

#endif
