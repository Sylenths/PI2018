#ifndef LABEL2D_H
#define LABEL2D_H

#include "includes.h"

class Label2d : public VisualEntity2d {
private:
    Texture2d texture;

public:
  Label2d(const std::string name, const Vector& position, Font* font, const std::string& text, const SDL_Color& color) : VisualEntity2d(name, position, Vector2d(0.0, 0.0)), texture("txtr" + name) {
      SDL_Surface* sdlSurface = TTF_RenderText_Blended(font->getFont(), text.c_str(), color);

      unsigned int ID;
      glGenTextures(1, &ID);
      glBindTexture(GL_TEXTURE_2D, ID);
      glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      texture.set(ID, sdlSurface->w, sdlSurface->h);
      SDL_FreeSurface(sdlSurface);
  }

  void draw() {
      glBindTexture(GL_TEXTURE_2D, texture.getID());
      glBegin(GL_QUADS);
          glTexCoord2d(0.0, 0.0);
          glVertex3d(position.x, position.y, 0.0);
          glTexCoord2d(1.0, 0.0);
          glVertex3d(position.x + texture.getWidth(), position.y, 0.0);
          glTexCoord2d(1.0, 1.0);
          glVertex3d(position.x + texture.getWidth(), position.y + texture.getHeight(), 0.0);
          glTexCoord2d(0.0, 1.0);
          glVertex3d(position.x, position.y + texture.getHeight(), 0.0);
      glEnd();
  }

  int getHeight() { return texture.getHeight(); }
  int getWidth() { return texture.getWidth(); }

  void notify(SDL_Event *sdlEvent) {}
};

#endif
