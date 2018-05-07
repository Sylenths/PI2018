/// \brief Gestionnaire de police d'écriture.
/// \details Permet de récupérer la police d'écriture..
/// \authors Antoine Legault, Guillaume Julien-Desmarchais
/// \date 24 mars 2018
/// \version 0.4
/// \warning Aucuns
/// \bug Aucuns
#ifndef SOURCE_FONT_H
#define SOURCE_FONT_H

class Font : public Resource {

private:
    TTF_Font* font; ///< Pointeur de font.

public:
	
    /// Constructeur.
	/// \param filename Nom du fichier contenant la police de caractères.
	/// \param pixelSize La taille des caractères.
    Font(const char* filename, int pixelSize = 12) { //
        font = TTF_OpenFont(filename, pixelSize);
    }
    
    /// Destructeur.
    ~Font() {
        TTF_CloseFont(font);
        font = nullptr; //To be safe...
    }

    TTF_Font* getFont(){
        return font;
    }

    const std::string getType() {
        return "Font";
    }
};


#endif
