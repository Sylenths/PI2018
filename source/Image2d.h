#ifndef IMAGE2D_H
#define IMAGE2D_H

#include "includes.h"

class Image2d : public VisualEntity2d {
private:
    Texture2d* defaultTexture;

public:
    Image2d(const std::string& name, const Vector& position, Texture2d* texture) : VisualEntity2d(name, position, Vector2d(texture->getWidth(), texture->getHeight())) {
        defaultTexture = texture;
        onClick = nullptr;
    }

    void draw() {
        glBindTexture(GL_TEXTURE_2D, defaultTexture->getID());
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(position.x, position.y, 0.0);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(position.x + defaultTexture->getWidth(), position.y, 0.0);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(position.x + defaultTexture->getWidth(), position.y + defaultTexture->getHeight(), 0.0);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(position.x, position.y + defaultTexture->getHeight(), 0.0);
        glEnd();
    }

    void notify(SDL_Event* sdlEvent) {
        if ((sdlEvent->button.x > position.x) && (sdlEvent->button.x < (position.x + defaultTexture->getWidth())) && (sdlEvent->button.y > position.y) && (sdlEvent->button.y < (position.y + defaultTexture->getHeight()))) {
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT) && onClick)
                        onClick();
                    break;

                case SDL_MOUSEMOTION:
                    //textureToDraw = textureIDs["over"];
                    break;
            }
        }
        //else
            //textureToDraw = textureIDs["default"];
    }
};

#endif
