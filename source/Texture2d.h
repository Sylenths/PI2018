#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "includes.h"

class Texture2d : public Entity {
private:
    unsigned int ID;
    int width, height;

public:
    Texture2d(const std::string& name, const char* fileName) : Entity(name) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        SDL_Surface* surface = IMG_Load(fileName);
        width = surface->w;
        height = surface->h;
        #if defined(_WIN32) || defined(__linux__)
          glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        #else
          glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
        #endif
        SDL_FreeSurface(surface);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    virtual ~Texture2d() {
        glDeleteTextures(1, &ID);
    }

    const unsigned int getID() const { return ID; }
    const int getWidth() const { return width; }
    const int getHeight() const { return height; }
};

#endif
