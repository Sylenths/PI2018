#ifndef IMAGE2D_H
#define IMAGE2D_H

#include "includes.h"

class Image2d : public VisualEntity2d {
private:
    Texture2d texture2d;

public:
  Image2d(const std::string& name, const char* fileName, const Vector& position, bool visible = true) : VisualEntity2d(name, position, visible), texture2d("txtr" + name, fileName) {}

  void draw() {
    glBindTexture(GL_TEXTURE_2D, texture2d.getID());
    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex3d(position.x, position.y, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex3d(position.x + texture2d.getWidth(), position.y, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex3d(position.x + texture2d.getWidth(), position.y + texture2d.getHeight(), 0.0);
        glTexCoord2d(0.0, 1.0);
        glVertex3d(position.x, position.y + texture2d.getHeight(), 0.0);
    glEnd();
  }

  virtual void notify(SDL_Event* sdlEvent) {}
};

#endif
