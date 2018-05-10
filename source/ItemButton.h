#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H
#include "includes.h"

#define RATIO 4.1875


class ItemButton : public VisualEntity2d {
protected:
    int TextureID;
    Image2d* backTexture[2];
    Image2d* image;
    Image2d* imageCurrency;
    Label2d* labelName;
    Label2d* labelPrice;

public:
    ItemButton(const std::string& name, const Vector& position, const double width, Font* font, std::string& textName, std::string& textPrice, const SDL_Color& color, Texture2d* image, Texture2d* imageCurrency, Texture2d* backTexture, Texture2d* hoverTexture = nullptr) : VisualEntity2d(name, position, Vector2d(width, width/RATIO)) {
        this->backTexture[0] = new Image2d("BackGroundTexture", position, backTexture);
        this->backTexture[1] = (hoverTexture) ? new Image2d("ButtonHover", position, hoverTexture) : nullptr;

        TextureID = 0;

        this->image = new Image2d("ImageItem", {position.x + width/33.5, position.y + (width/RATIO)/16.0}, image, width/6.0909, (width/RATIO)/1.0666);
        this->imageCurrency = new Image2d("ImageCurency", {position.x + width/4.4666, position.y + (width/RATIO)/1.7777}, image, width/11.1666, (width/RATIO)/2.6666);

        int wpoint;
        TTF_SizeText(font->getFont(), "...", &wpoint, NULL);
        int w;
        bool textShorted = false;
        TTF_SizeText(font->getFont(), textName.c_str(), &wpoint, NULL);
        while(double(w + wpoint) >= (width - width/2.9130)) {
            TTF_SizeText(font->getFont(), textName.c_str(), &wpoint, NULL);
            textName.pop_back();
            textShorted = true;
        }
        if(textShorted) {
            textName.push_back('.');
            textName.push_back('.');
            textName.push_back('.');
        }

        this->labelName = new Label2d("lblTitle", {position.x + width/4.4666, position.y + (width/RATIO)/5.3333}, font, textName, color);
        this->labelPrice = new Label2d("lblPrice", {position.x + width/2.9130, position.y + (width/RATIO)/1.7777}, font, textPrice, color);

        onClick = nullptr;

    }

    ~ItemButton() {
        delete backTexture[0];
        delete backTexture[1];
        delete image;
        delete imageCurrency;
        delete labelName;
        delete labelPrice;
    }

    void draw() {
        backTexture[TextureID]->draw();
        image->draw();
        imageCurrency->draw();
        labelName->draw();
        labelPrice->draw();
    }

    void notify(SDL_Event *sdlEvent) {
        if ((sdlEvent->button.x > position.x) && (sdlEvent->button.x < (position.x + size.x)) && (sdlEvent->button.y > position.y) && (sdlEvent->button.y < (position.y + size.y))) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick) onClick();
                    break;

                case SDL_MOUSEMOTION:
                    if (backTexture[1]) TextureID = 1;
                    break;
            }
        }
        else
            TextureID = 0;
    }
};

#endif
