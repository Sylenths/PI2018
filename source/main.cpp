#include "ProjetFinal.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    ProjetFinal::getInstance()->run();
    ProjetFinal::deleteInstance();

    SDL_Quit();
    return 0;
}
