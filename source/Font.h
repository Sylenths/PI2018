/// \brief Gestionnaire de police d'écriture.
/// \details Permet de récupérer la police d'écriture..
/// \authors Antoine Legault, Guillaume Julien-Desmarchais
/// \date 24 mars 2018
/// \version 0.4
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SOURCE_FONT_H
#define SOURCE_FONT_H

#include <SDL2/SDL_ttf.h>
#include "Resource.h"
#include "ResourceManager.h"
class Font : public Resource{

private:
    TTF_Font* font; ///< Pointeur de font.

    public:

    /// Constructeur.
	/// \param filename Nom du font
	/// \param RessourceName Nom de la ressource
	/// \param pixelSize La taille de pixel
    Font(const char* filename, const char* RessourceName, int pixelSize = 12){ //
        font = TTF_OpenFont(filename, pixelSize);
        ResourceManager::getInstance()->addResource(RessourceName, this);
    }
    
    /// Destructeur.
    ~Font(){
        TTF_CloseFont(font);
        font = nullptr; //To be safe...
    }
};


#endif
