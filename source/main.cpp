#include "ProjetFinal.h"

int main(int argc, char* argv[]) {
    //Test PowerManager

    PowerAppareil* app1 = new PowerAppareil(100.0);
    PowerAppareil* app2 = new PowerAppareil(100.0);
    PowerAppareil* app3 = new PowerAppareil(100.0);
    PowerAppareil* app4 = new PowerAppareil(100.0);
    PowerAppareil* app5 = new PowerAppareil(100.0);
    PowerSource* src1 = new PowerSource(100.0);
    PowerSource* src2 = new PowerSource(100.0);
    PowerSource* src3 = new PowerSource(100.0);
    PowerSource* src4 = new PowerSource(100.0);

    PowerManager* pwr = new PowerManager();

    pwr->addAppareil(app1);
    pwr->addAppareil(app2);
    pwr->addAppareil(app3);
    pwr->addAppareil(app4);
    pwr->addAppareil(app5);
    pwr->addSource(src1);
    pwr->addSource(src2);
    pwr->addSource(src3);
    pwr->addSource(src4);

    pwr->createWire(app1->getKey(), src4->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app1->getKey(), src1->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app2->getKey(), src2->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app3->getKey(), src2->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app4->getKey(), src2->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app4->getKey(), src3->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app4->getKey(), app5->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(src2->getKey(), src1->getKey(), 20.0, 0.001, GOLD);


    pwr->getShortestPath(app1);
    pwr->getShortestPath(app2);
    pwr->getShortestPath(app3);
    pwr->getShortestPath(app4);
    pwr->getShortestPath(app5);

    pwr->updatePower();
    //(*app5->getPathMap())[0].pop();
    //int front = (*app5->getPathMap())[0].front();












    srand(time(0));

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

    EntityManager::add(new Font("font - arial12", "../Fonts/arial.ttf", 72));
    EntityManager::add(new Font("font - arial28", "../Fonts/arial.ttf", 50));
    EntityManager::add(new Font("font - arial30", "../Fonts/arial.ttf", 30));
    EntityManager::add(new Font("font - arial32", "../Fonts/arial.ttf", 15));
    ProjetFinal::getInstance()->run(filePath.c_str());
    ProjetFinal::getInstance()->deleteInstance();
    EntityManager::destroy();

    Chrono tst;
    std::cout << tst.getElapsed(SECONDS) << std::endl;

    TTF_Quit();
    SDL_Quit();

    return 0;
}
