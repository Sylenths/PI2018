#include "ProjetFinal.h"
#include "Matrix.h"
#include "Label.h"


int main(int argc, char* argv[]) {
    std::string filePath = argv[0];

    /* Échoue sous *NIX / Mac OSX et fait planter (SIGSEGV) le programme.
     * (les systèmes unix-like (Linux, Mac OSX, ...) utilisent "/" pour séparer les dossiers ...)
     * il faudrait détecter l'OS ou utiliser des #define pour compiler du code spécifique pour chaque OS pour que ça fonctionne.

    while (filePath.back() != '\\') { // On doit écrire backslash deux fois de suite, car c'est un caractère spécial pour C et C++.
        filePath.pop_back();
    }
     */

    while (filePath.back() != '/') { // On doit écrire backslash deux fois de suite, car c'est un caractère spécial pour C et C++.
        filePath.pop_back();
    }

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    ResourceManager::getInstance()->addResource("font - arial12",new Font("../Fonts/arial.ttf"));
    ProjetFinal::getInstance()->run(filePath.c_str());


    ProjetFinal::deleteInstance();
    ResourceManager::deleteInstance();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
