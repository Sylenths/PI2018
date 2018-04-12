/// \brief Classe de parametre d'action
/// \details Classe abstraite qui sera parent de tout les types de paramètres
/// \author Mickaël Grisé-Roy
/// \date 10 Avril 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SOURCE_SIMPARAMETER_H
#define SOURCE_SIMPARAMETER_H


#define SIMINT 1
#define SIMDOUBLE 2

#include "includes.h"
class ActionParameter{
protected:
    std::string name;///< le nom du param

public:
    /// Constructeur
    /// \param name Le nom du param
    ActionParameter(std::string name){
        this->name = name;
    }

    /// retourne le type de Param
    virtual int getType() = 0;
};

#endif
