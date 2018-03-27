#include <string>

#include "ProjetFinal.h"
#include "Matrix.h"


int main(int argc, char* argv[]) {
    std::string path = argv[0];

    SDL_Init(SDL_INIT_VIDEO);
    ProjetFinal::getInstance()->setDefaultPath(path);
    ProjetFinal::getInstance()->run();



    ProjetFinal::deleteInstance();
    SDL_Quit();
    return 0;
}
