#ifndef BUTTON2D_H
#define BUTTON2D_H

#include "includes.h"

class Button2d : public VisualEntity2d {
public:
    Button2d(const std::string& name, const Vector& position, const Vector2d& size) : VisualEntity2d(name, position, size) {
        onClick = nullptr;
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

    void draw() {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);

        glBegin(GL_QUADS);
            glColor3d(1.0, 1.0, 1.0);
            glVertex3d(position.x, position.y, 0.0);
            glVertex3d(position.x + size.x, position.y, 0.0);
            glVertex3d(position.x + size.x, position.y + size.y, 0.0);
            glVertex3d(position.x, position.y + size.y, 0.0);
        glEnd();

        glDisable(GL_COLOR);
        glEnable(GL_TEXTURE_2D);
    }
};

#endif
