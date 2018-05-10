#ifndef LABEL2D_H
#define LABEL2D_H

#include "includes.h"

class Label2d : public VisualEntity2d {
public:
  Texture2d texture;

  Label2d(const std::string name, const Vector& position, Font* font, const std::string& text, const SDL_Color& color) : VisualEntity2d(name, position, Vector2d(0.0, 0.0)), texture("txtr" + name) {
      setText(font, text, color);
  }

  void setText(Font* font, const std::string& text, const SDL_Color& color) {
      SDL_Surface* sdlSurface = TTF_RenderText_Blended(font->getFont(), text.c_str(), color);
      texture.width = sdlSurface->w;
      texture.height = sdlSurface->h;

      glDeleteTextures(1, &texture.ID);
      glGenTextures(1, &texture.ID);
      glBindTexture(GL_TEXTURE_2D, texture.ID);
      glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, sdlSurface->w, sdlSurface->h,0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
      SDL_FreeSurface(sdlSurface);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  void draw() {
      glBindTexture(GL_TEXTURE_2D, texture.ID);
      glBegin(GL_QUADS);
          glTexCoord2d(0.0, 0.0);
          glVertex3d(position.x, position.y, 0.0);
          glTexCoord2d(1.0, 0.0);
          glVertex3d(position.x + texture.width, position.y, 0.0);
          glTexCoord2d(1.0, 1.0);
          glVertex3d(position.x + texture.width, position.y + texture.height, 0.0);
          glTexCoord2d(0.0, 1.0);
          glVertex3d(position.x, position.y + texture.height, 0.0);
      glEnd();
  }

  void notify(SDL_Event *sdlEvent) {}
};

#endif
