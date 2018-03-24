/// \brief Représentation de tous les ressources utilisées dans le projet.
/// \details Interface permettant d'avoir acces, de rajouter ou d'enlever des textures ou des fonts.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef SOURCE_RESOURCEMANAGER_H
#define SOURCE_RESOURCEMANAGER_H

#include <map>
#include "Resource.h"

class ResourceManager {
private:
    std::map<std::string, Resource*> textures;  ///< Composante Map de textures.
    std::map<std::string, Resource*> fonts;     ///< Composante Map de polices d'écriture.
public:
    /// Ajouter une texture.
    void addResource(){

    }
    /// Supprimer une texture.
    void removeResource(){

    }
    /// Récupérer une texture.
    void getResource(){

    }
};


#endif
