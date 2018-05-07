/// \brief Gestionnaire de toutes les ressources utilisées dans le projet.
/// \details Gère et permet d'avoir accès à, de rajouter ou d'enlever des images, des textures, des modèles 3D et des polices de caractères associés à un nom.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.2
/// \warning Ajouter avec add() une ressource dont le nom est déjà utilisé écrasera l'ancienne ressource et causera une fuite de mémoire. removeResource() détruit la ressource en plus de libérer son identificateur.
/// \bug Aucun.

#ifndef SOURCE_RESOURCEMANAGER_H
#define SOURCE_RESOURCEMANAGER_H

class EntityManager {
private:
    static std::map<std::string, Entity*> entities;  ///< Ressources.

public:
	/// Destruction de toutes les ressources vers la fin du jeu.
    static void destroy() {
        /*
        std::map<std::string, Entity*>::iterator it = entities.begin();
        while(it != entities.end()) {
            if ((*it).second) delete ((*it).second);// (*it).second is the Resource* of the current map "container"
            it = entities.erase(it);// Remove map "container" at current it position then set it to next map "container".
		}
        */
	}

	/// Ajouter une ressource.
    static void add(Entity* entity) {
        entities[entity->getName()] = entity;
	}

	/// Supprimer une ressource AVEC DESTRUCTEUR. ATTENTION!
    static void remove(std::string resourceKey) {
        if(entities[resourceKey]) {
            delete entities[resourceKey];
            entities.erase(resourceKey);
		}
	}

	/// Récupérer une ressource.
    template <typename T>
    static T get(std::string name) {
        return (T)entities[name];
	}
};

std::map<std::string, Entity*> EntityManager::entities;

#endif
