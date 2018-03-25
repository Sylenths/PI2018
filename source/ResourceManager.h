/// \brief Représentation de tous les ressources utilisées dans le projet.
/// \details Interface permettant d'avoir acces, de rajouter ou d'enlever des textures ou des fonts.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li
/// \date 24 mars 2018
/// \version 0.1
/// \warning Si vous utilisez la méthode add avec un nom qui est déjà utilisé cela écrasera l'ancienne resource. Aussi, il y a une destruction des données chaque fois que la méthode removeResource() est appelée.
/// \bug Problèmes connus, le destructeur de fin de jeu ne fonctionne pas en code

#ifndef SOURCE_RESOURCEMANAGER_H
#define SOURCE_RESOURCEMANAGER_H

#include <iterator>
#include <map>
#include "Resource.h"

class ResourceManager {
private:
    std::map<std::string, Resource*> resources;  ///< Composante Map de textures.
public:

    /// Destruction de toutes les ressources vers la fin du jeu. Utilisation de la magie auto.
    ~ResourceManager() { /*
        typename std::map<std::string, Resource*>::iterator it = resources.begin();
        for (int i = 0; i <resources.size() ; ++i) {
            delete resources[(it)];
        }
        */
        resources.clear();
    }

    /// Ajouter une ressource.
    void addResource(std::string resourceKey, Resource* resource){
        resources[resourceKey] = resource;
    }
    /// Supprimer une ressource AVEC DESTRUCTEUR. ATTENTION!
    void removeResource(std::string resourceKey){
        if(resources[resourceKey]) {
            delete resources[resourceKey];
            resources.erase(resourceKey);
        }
    }
    /// Récupérer une ressource.
    Resource* getResource(std::string resourceKey){
        if(resources[resourceKey])
            return resources[resourceKey];
    }
};


#endif
