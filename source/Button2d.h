#ifndef BUTTON2D_H
#define BUTTON2D_H

#include "includes.h"

class Button2d : public VisualEntity2d {
private:
    Image2d* background;
    Label2d* title;

public:
    Button2d(const std::string& name, const Vector& position, Texture2d* texture, Font* font, const std::string& text, const SDL_Color& color) : VisualEntity2d(name, position, Vector2d(texture->width, texture->height)) {
        onClick = nullptr;
        background = new Image2d("ButtonBackground", position, texture);
        title = new Label2d("lblButtonTitle", position, font, text, color);
        title->position.x = (size.x / 2.0) - (title->texture.width / 2.0) + position.x;
        title->position.y = (size.y / 2.0) - (title->texture.height / 2.0) + position.y;
    }

    ~Button2d() {
        delete title;
        delete background;
    }

    void draw() {
        background->draw();
        title->draw();
    }

    void notify(SDL_Event *sdlEvent) {
        if ((sdlEvent->button.x > position.x) && (sdlEvent->button.x < (position.x + size.x)) && (sdlEvent->button.y > position.y) && (sdlEvent->button.y < (position.y + size.y))) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick) onClick();
                    break;
            }
        }
    }
};

#endif
