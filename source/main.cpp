#include "ProjetFinal.h"
#include "Matrix.h"


int main(int argc, char* argv[]) {
    std::string filePath = argv[0];

    while (filePath.back() != '\\') { // On doit écrire backslash deux fois de suite, car c'est un caractère spécial pour C et C++.
        filePath.pop_back();
    }

    SDL_Init(SDL_INIT_VIDEO);
    ProjetFinal::getInstance()->run(filePath.c_str());

    ProjetFinal::deleteInstance();
    ResourceManager::deleteInstance();
    SDL_Quit();
    return 0;
}
