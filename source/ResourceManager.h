/// \brief Représentation de tous les ressources utilisées dans le projet.
/// \details Interface permettant d'avoir acces, de rajouter ou d'enlever des textures ou des fonts.
/// \author Antoine Legault, Jade St-Pierre Bouchard
/// \date 24 mars 2018
/// \version 0.1
/// \warning Si vous utilisez la méthode add avec un nom qui est déjà utilisé cela écrasera l'ancienne resource.
/// \bug Problèmes connus

#ifndef SOURCE_RESOURCEMANAGER_H
#define SOURCE_RESOURCEMANAGER_H

#include <map>
#include "Resource.h"

class ResourceManager {
private:
    std::map<std::string, Resource*> resources;  ///< Composante Map de textures.
public:
    /// Ajouter une texture.
    void addResource(std::string resourceKey, Resource* resource){
        resources[resourceKey] = resource;
    }
    /// Supprimer une texture.
    void removeResource(std::string resourceKey){
        if(resources[resourceKey])
            resources.erase(resourceKey);

    }
    /// Récupérer une texture.
    Resource* getResource(std::string resourceKey){
        if(resources[resourceKey])
            return resources[resourceKey];

    }
};


#endif
