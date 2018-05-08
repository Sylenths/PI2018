#include "ProjetFinal.h"

int main(int argc, char* argv[]) {
    //Test PowerManager

    PowerAppareil* app1 = new PowerAppareil(100.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerAppareil* app2 = new PowerAppareil(100.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerAppareil* app3 = new PowerAppareil(100.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerAppareil* app4 = new PowerAppareil(100.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerAppareil* app5 = new PowerAppareil(100.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerSource* src0 = new PowerSource(150.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerSource* src1 = new PowerSource(150.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerSource* src2 = new PowerSource(150.0, "", 0.0, 0.0, 0.0, 1, false);
    PowerSource* src3 = new PowerSource(150.0, "", 0.0, 0.0, 0.0, 1, false);

    PowerManager* pwr = new PowerManager();

    pwr->addAppareil(app1);
    pwr->addAppareil(app2);
    pwr->addAppareil(app3);
    pwr->addAppareil(app4);
    pwr->addAppareil(app5);
    pwr->addSource(src0);
    pwr->addSource(src1);
    pwr->addSource(src2);
    pwr->addSource(src3);

    pwr->createWire(app1->getKey(), src3->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app1->getKey(), src0->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app2->getKey(), src1->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app3->getKey(), src1->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app4->getKey(), src1->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app4->getKey(), src2->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(app4->getKey(), app5->getKey(), 20.0, 0.001, GOLD);
    pwr->createWire(src1->getKey(), src0->getKey(), 20.0, 0.001, GOLD);


    pwr->getShortestPath(app1);
    pwr->getShortestPath(app2);
    pwr->getShortestPath(app3);
    pwr->getShortestPath(app4);
    pwr->getShortestPath(app5);

    pwr->updatePower();
    pwr->seePower();


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
