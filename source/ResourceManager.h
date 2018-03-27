/// \brief Gestionnaire de toutes les ressources utilisées dans le projet.
/// \details Gère et permet d'avoir accès à, de rajouter ou d'enlever des images, des textures, des modèles 3D et des polices de caractères associés à un nom.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.2
/// \warning Ajouter avec add() une ressource dont le nom est déjà utilisé écrasera l'ancienne ressource et causera une fuite de mémoire. removeResource() détruit la ressource en plus de libérer son identificateur.
/// \bug Aucun.

#ifndef SOURCE_RESOURCEMANAGER_H
#define SOURCE_RESOURCEMANAGER_H

#include <iterator>
#include <map>
#include "Singleton.h"
#include "Resource.h"

class ResourceManager : public Singleton<ResourceManager> {
private:
    std::map<std::string, Resource*> resources;  ///< Map de ressources.
    std::map<std::string, unsigned int> textures;
public:

	/// Destruction de toutes les ressources vers la fin du jeu.
	~ResourceManager() {

		std::map<std::string, Resource*>::iterator it = resources.begin();
		while(it != resources.end()){
			delete ((*it).second);// (*it).second is the Resource* of the current map "container"
			it = resources.erase(it);// Remove map "container" at current it position then set it to next map "container".
		}
	}

	/// Ajouter une ressource.
    void addResource(std::string resourceKey, Resource* resource) {
		resources[resourceKey] = resource;
	}
	/// Supprimer une ressource AVEC DESTRUCTEUR. ATTENTION!
    void removeResource(std::string resourceKey) {
		if(resources[resourceKey]) {
			delete resources[resourceKey];
			resources.erase(resourceKey);
		}
	}
	/// Récupérer une ressource.
    Resource* getResource(std::string resourceKey) {
		if(resources[resourceKey])
			return resources[resourceKey];
	}

    void addTexture(std::string textureKey, unsigned int textureID) {
        textures[textureKey] = textureID;
    }

    void removeTexture(std::string textureKey) {
        if(textures[textureKey]) {
            textures.erase(textureKey);
        }
    }

    unsigned int getTexture(std::string textureKey) {
        if(textures[textureKey]) {
            return textures[textureKey];
        }
    }
};


#endif
