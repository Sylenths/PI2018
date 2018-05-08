#ifndef BUTTON2D_H
#define BUTTON2D_H

#include "includes.h"

class Button2d : public VisualEntity2d {
private:
    int textureID;
    Image2d* images[2];
    Label2d* title;

public:
    Button2d(const std::string& name, const Vector& position, Font* font, const std::string& text, const SDL_Color& color, Texture2d* backTexture, Texture2d* hoverTexture = nullptr) : VisualEntity2d(name, position, Vector2d(backTexture->width, backTexture->height)) {
        images[0] = new Image2d("ButtonBackground", position, backTexture);
        images[1] = (hoverTexture) ? new Image2d("ButtonHover", position, hoverTexture) : nullptr;
        textureID = 0;

        title = new Label2d("lblButtonTitle", position, font, text, color);
        title->position.x = (size.x / 2.0) - (title->texture.width / 2.0) + position.x;
        title->position.y = (size.y / 2.0) - (title->texture.height / 2.0) + position.y;

        onClick = nullptr;
    }

    ~Button2d() {
        delete title;
        delete images[0];
        delete images[1];
    }

    void draw() {
        images[textureID]->draw();
        title->draw();
    }

    void notify(SDL_Event *sdlEvent) {
        if ((sdlEvent->button.x > position.x) && (sdlEvent->button.x < (position.x + size.x)) && (sdlEvent->button.y > position.y) && (sdlEvent->button.y < (position.y + size.y))) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick) onClick();
                    break;

                case SDL_MOUSEMOTION:
                    if (images[1]) textureID = 1;
                    break;
            }
        }
        else
            textureID = 0;
    }
};

#endif
