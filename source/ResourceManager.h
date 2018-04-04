/// \brief Gestionnaire de toutes les ressources utilisées dans le projet.
/// \details Gère et permet d'avoir accès à, de rajouter ou d'enlever des images, des textures, des modèles 3D et des polices de caractères associés à un nom.
/// \author Antoine Legault, Jade St-Pierre Bouchard, Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.2
/// \warning Ajouter avec add() une ressource dont le nom est déjà utilisé écrasera l'ancienne ressource et causera une fuite de mémoire. removeResource() détruit la ressource en plus de libérer son identificateur.
/// \bug Aucun.

#ifndef SOURCE_RESOURCEMANAGER_H
#define SOURCE_RESOURCEMANAGER_H

class ResourceManager : public Singleton<ResourceManager> {
private:
    std::map<std::string, Resource*> resources;  ///< Map de ressources.
    std::map<std::string, unsigned int> textures;
public:

	/// Destruction de toutes les ressources vers la fin du jeu.
	~ResourceManager() {

		std::map<std::string, Resource*>::iterator it = resources.begin();
		while(it != resources.end()) {
			delete ((*it).second);// (*it).second is the Resource* of the current map "container"
			it = resources.erase(it);// Remove map "container" at current it position then set it to next map "container".
		}

        std::map<std::string, unsigned int>::iterator ittex = textures.begin();
        while(ittex != textures.end()) {
            glDeleteTextures(1,&((*ittex).second));// (*it).second is the Resource* of the current map "container"
            ittex = textures.erase(ittex);// Remove map "container" at current it position then set it to next map "container".
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
    template <typename T>
    T getResource(std::string resourceKey) {
		if(resources[resourceKey])
			return (T)resources[resourceKey];
	}
	/// Ajouter une paire nom / identifiant numérique de texture OpenGL.
	/// \param textureKey Nom de la texture.
	/// \param textureID Identifiant numérique de texture OpenGL.
    void addTexture(std::string textureKey, unsigned int textureID) {
        textures[textureKey] = textureID;
    }

	/// Supprimer un identifiant numérique de texture OpenGL.
	/// \param textureKey Nom de la texture.
    void removeTexture(std::string textureKey) {
        if(textures[textureKey]) {
            glDeleteTextures(1,&textures[textureKey]);
            textures.erase(textureKey);
        }
    }
	/// Récupérer l'identifiant de texture OpenGL à partir du nom d'une texture.
	/// \param textureKey Nom de la texture.
	/// \return Identifiant numérique de texture OpenGL.
    unsigned int getTexture(std::string textureKey) {
        if(textures[textureKey]) {
            return textures[textureKey];
        }
    }
};


#endif
