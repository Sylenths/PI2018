#include "ProjetFinal.h"

int main(int argc, char* argv[]) {
    std::string filePath = argv[0];
    #ifdef _WIN32
    while (filePath.back() != '\\') {
        filePath.pop_back();
    }
    #else
    while (filePath.back() != '/') {
        filePath.pop_back();
    }
    #endif

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ResourceManager::getInstance()->addResource("font - arial12",new Font("../Fonts/arial.ttf", 72));
    ResourceManager::getInstance()->addResource("font - arial28",new Font("../Fonts/arial.ttf", 28));
    ProjetFinal::getInstance()->run(filePath.c_str());
    ProjetFinal::deleteInstance();
    ResourceManager::deleteInstance();

    TTF_Quit();
    SDL_Quit();

    return 0;
}
