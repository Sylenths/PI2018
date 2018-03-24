
#include "ProjetFinal.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    ProjetFinal* projet = new ProjetFinal("SDL - OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, 0);
    //glContext.setFrustum(90.0, 0.1, 1000.0);

    projet->run();

    SDL_Quit();

    delete (projet);

    return 0;
}