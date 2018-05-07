/// \brief Gestionnaire de police d'écriture.
/// \details Permet de récupérer la police d'écriture..
/// \authors Antoine Legault, Guillaume Julien-Desmarchais
/// \date 24 mars 2018
/// \version 0.4
/// \warning Aucuns
/// \bug Aucuns

#ifndef SOURCE_FONT_H
#define SOURCE_FONT_H

class Font : public Entity {

private:
    TTF_Font* font; ///< Pointeur de font.

public:
	
    /// Constructeur.
	/// \param filename Nom du fichier contenant la police de caractères.
	/// \param pixelSize La taille des caractères.
    Font(const std::string& name, const char* filename, int pixelSize = 12) : Entity(name) { //
        font = TTF_OpenFont(filename, pixelSize);
    }
    
    /// Destructeur.
    ~Font() {
        TTF_CloseFont(font);
    }

    TTF_Font* getFont(){
        return font;
    }
};

#endif
