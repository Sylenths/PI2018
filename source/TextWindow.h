
#ifndef SOURCE_TEXTWINDOW_H
#define SOURCE_TEXTWINDOW_H

#include "includes.h"

class TextWindow : public Model{
private:
    std::list<Label*> labelList;
    std::string text;
    Model* modelToSubcribe;
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
    TextWindow(TTF_Font* font, SDL_Color color, std::string text, unsigned int x, unsigned int y, unsigned int z, unsigned int w, unsigned h, Model* modelToSubscribe = nullptr, unsigned int textureID = 0) : Model(x, y, z, textureID, false) {
        this->text = text;
        this->modelToSubcribe = modelToSubscribe;
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
        int textWindowWidth = 0;
        int textWindowHeight = 0;
        int spacePosition = 0;
        int lastPosition = 0;
        for(int i = 0; i <= text.size(); i++){
            if(i != 0)
                width++;
            runner = text[i];
            if(runner == ' '){
                spacePosition = i;
            }
            TTF_SizeText(font, text.substr(lastPosition, width).c_str(), &textWindowWidth, &textWindowHeight);
            if(runner == '\n' || textWindowWidth >= w || i == text.size() ){
                if(height == y && runner != '\n'){
                    labelList.push_back(new Label(font, color, text.substr(0, spacePosition).c_str(), x, height , z));
                    lastPosition = spacePosition + 1;
                }
                if(height == y && runner == '\n'){
                    labelList.push_back(new Label(font, color, text.substr(0, i).c_str(), x, height , z));
                    lastPosition = i;
                }
                if(textWindowWidth >= w && height != y){
                    labelList.push_back(new Label(font, color, text.substr(lastPosition, spacePosition - lastPosition).c_str(), x, height , z));
                    lastPosition = spacePosition + 1;
                }
                if( runner == '\n' && height != y){
                    labelList.push_back(new Label(font, color, text.substr(lastPosition + 1, width).c_str(), x, height , z));
                    lastPosition = i;
                }

                if(i == text.size()){
                    labelList.push_back(new Label(font, color, text.substr(lastPosition, i - lastPosition).c_str(), x, height , z));
                }

                height += 15;
                width = 0;
            }


        }
        if(labelList.empty())
            labelList.push_back(new Label(font, color, text.c_str(), x, y , z));

    }
    void draw(){
        if(((CheckBox*)modelToSubcribe)->getMouseOver())
            for (auto it : labelList)
                it->draw();
    }

};


#endif
