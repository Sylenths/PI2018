/// \brief Représentation d'une resource.
/// \details Classe virtuelle.
/// \author Patrick Singcaster
/// \date 6 mai 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
    virtual const std::string getType() = 0;
};

#endif
