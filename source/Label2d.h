#ifndef LABEL2D_H
#define LABEL2D_H

#include "includes.h"

class Label2d : public VisualEntity2d {
private:
    Texture2d defaultTexture;

public:
  Label2d(const std::string name, const Vector& position, Font* font, const std::string& text, const SDL_Color& color) : VisualEntity2d(name, position, Vector2d(0.0, 0.0)), defaultTexture("txtr" + name) {
      SDL_Surface* sdlSurface = TTF_RenderText_Blended(font->getFont(), text.c_str(), color);

      unsigned int ID;
      glGenTextures(1, &ID);
      glBindTexture(GL_TEXTURE_2D, ID);
      glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      defaultTexture.set(ID, sdlSurface->w, sdlSurface->h);
      SDL_FreeSurface(sdlSurface);
  }

  void draw() {
      glBindTexture(GL_TEXTURE_2D, defaultTexture.getID());
      glBegin(GL_QUADS);
          glTexCoord2d(0.0, 0.0);
          glVertex3d(position.x, position.y, 0.0);
          glTexCoord2d(1.0, 0.0);
          glVertex3d(position.x + defaultTexture.getWidth(), position.y, 0.0);
          glTexCoord2d(1.0, 1.0);
          glVertex3d(position.x + defaultTexture.getWidth(), position.y + defaultTexture.getHeight(), 0.0);
          glTexCoord2d(0.0, 1.0);
          glVertex3d(position.x, position.y + defaultTexture.getHeight(), 0.0);
      glEnd();
  }

  int getHeight() { return defaultTexture.getHeight(); }
  int getWidth() { return defaultTexture.getWidth(); }

  void notify(SDL_Event *sdlEvent) {}
};

#endif
