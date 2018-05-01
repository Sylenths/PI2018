
#ifndef SOURCE_TEXTWINDOW_H
#define SOURCE_TEXTWINDOW_H

#include "includes.h"

class TextWindow : public Model{
private:
    std::list<Label*> labelList;
    std::string text;
    int w;
    int x;
    int y;
    int z;
    SDL_Color color;
    TTF_Font* font;
public:
    /// Ajoute la texture avec le texte dans le resourceManager
    /// \param font Police de caractères
    /// \param color Couleur du texte.
    /// \param text Texte affiché.
    /// \param x Position en x par rapport au coin supérieur gauche.
    /// \param y Position en y par rapport au coin supérieur gauche.
    /// \param width Largeur de l'image.
    /// \param height Hauteur de l'image.
    TextWindow(TTF_Font* font, SDL_Color color, std::string text, unsigned int x, unsigned int y, unsigned int z, unsigned int w, unsigned h, unsigned int textureID = 0) : Model(x, y, z, textureID, false) {
        this->text = text;
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
        this->color = color;
        this->font = font;
        cutTextForBox();
    }

    void cutTextForBox(){
        char runner;
        int height = y;
        int width = 0;
        for(int i = 0; i < text.size(); i++){
            runner = text[i];
            if(runner == '\n' || width >= w || i == (text.size() - 1) ){
                if(height == y){
                    labelList.push_back(new Label(font, color, text.substr( 0 , i).c_str(), x, height , z));
                }
                else
                    labelList.push_back(new Label(font, color, text.substr(i - width + 1, width).c_str(), x, height , z));
                height += 15;
                width = 0;
            }
            width++;

        }
        if(labelList.empty())
            labelList.push_back(new Label(font, color, text.c_str(), x, y , z));

    }

    void draw(){
        for (auto it : labelList)
            it->draw();
    }

};


#endif
