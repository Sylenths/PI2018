#ifndef BUTTON2D_H
#define BUTTON2D_H

#include "includes.h"

class Button2d : public VisualEntity2d {
private:
    Label2d label2d;

public:
    Button2d(const std::string& name, const Vector& position, const Vector2d& size, Font* font, const std::string& text, const SDL_Color& color) : VisualEntity2d(name, position, size), label2d("lbl" + name, position, font, text, color) {
        onClick = nullptr;
        label2d.position.x = (size.x / 2.0) - (label2d.getWidth() / 2.0) + position.x;
        label2d.position.y = (size.y / 2.0) - (label2d.getHeight() / 2.0) + position.y;
    }

    void draw() {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);

        glBegin(GL_QUADS);
            glColor4d(1.0, 1.0, 1.0, 0.5);
            glVertex3d(position.x, position.y, 0.0);
            glVertex3d(position.x + size.x, position.y, 0.0);
            glVertex3d(position.x + size.x, position.y + size.y, 0.0);
            glVertex3d(position.x, position.y + size.y, 0.0);
        glEnd();

        glDisable(GL_COLOR);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        label2d.draw();
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
