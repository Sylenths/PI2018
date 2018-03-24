#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "GLContext.h"
#include "Matrix.h"
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_VIDEO);

    GLContext glContext("SDL - OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, 0);
    //glContext.setFrustum(90.0, 0.1, 1000.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    SDL_ShowCursor(SDL_DISABLE);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    SDL_Event sdlEvent;
    /*
     * déplacement de la souris
    sdlEvent.motion.xrel;

     */
    bool isOpen = true;
    while (isOpen){
        while(SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    isOpen = false;
                    break;
            }
        }
        glContext.clear();
        glContext.refresh();
    }

    SDL_Quit();

    return 0;
}