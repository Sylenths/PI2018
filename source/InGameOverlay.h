/// \brief Représentation de l'interface en jeu.
/// \details Interface pour construire et pour donner les informations sur la partie.
/// \author Antoine Legault , Guillaume Julien - Desmarchais
/// \date 24 mars 2018
/// \version 0.7
/// \warning Manque la boussole (pour indiquer le sens du vent) et le compte a rebours. Les labels ne s'ajuste pas selon la grosseur du nombre.
/// \bug Problemes non connus
#ifndef SOURCE_INGAMEOVERLAY_H
#define SOURCE_INGAMEOVERLAY_H
#include "includes.h"
#include <queue>
#include "Menu.h"
#include "Action.h"
#include "Build.h"

class InGameOverlay : public Menu, public Observer <SDL_Event*>{
private:
    bool isConstructingFondation;
    bool activeHud;///< Bool qui determine si le hud est affiché
    Camera* camera;

    std::list<Image*> alertsList;///< Liste alerte annoncant les intempéries a venir
    std::list<Image*> logoList;///< Liste d'image contenant les logo a afficher
    std::queue<Action*>* actionQueue;
    std::map<std::string, Button*> buttonMap;///< Map de bouton pour la construction de structure et le skip turn.
    std::map<std::string, Label*> labelMap;///< Label à afficher (principalement les ressources)

    //RotatingImage* windIndicator;

public:
    /// Constructeur.
    /// \param powerCount Nombre d'électricité disponible.
    /// \param simCoinCount Nombre de SIMcoins disponible
    /// \param temperatureC La temperature en celsius
    /// \param sunPower Puissance du soleil en pourcentage
    /// \param windSpeed Force du vent en pourcentage
    /// \param timeLeft Temps restant à la phase de construction.
    InGameOverlay(unsigned int powerCount = 0, unsigned int simCoinCount = 0, unsigned int temperatureC = 0, unsigned int sunPower = 0, Vector windSpeed = {0, 0, 0}, unsigned int timeLeft = 0) {
        activeHud = true;
        loadHUDTexture(powerCount, simCoinCount, temperatureC, sunPower, windSpeed.getNorm(), timeLeft);
        actionQueue = new std::queue<Action*>;
        isConstructingFondation = false;
        camera = new Camera({ 0.0, 3.5, 0.0 }, { 0.0, 3.5, -1.0 }, { 0.0, 1.0, 0.0 });
        camera->loadViewMatrix();

    }

    std::queue<Action*>* getActions(){
            return actionQueue;
    }
    Camera* getCamera(){
        return camera;
    }


    /// Affiche le InGameOverlay.
    void draw(){
        if(activeHud) {

            for (auto it : logoList) {
                it->draw();
            }
            for (auto it : alertsList) {
                it->draw();
            }
            for (auto it : labelMap) {
                it.second->draw();
            }
            for (auto it : buttonMap) {
                it.second->draw();
            }
        }
    }

    /// Cree les models necessaires pour le InGameOverlay.
    /// \param powerCount Nombre d'électricité disponible.
    /// \param simCoinCount Nombre de SIMcoins disponible
    /// \param temperatureC La température en celsius
    /// \param sunPower Puissance du soleil en pourcentage
    /// \param windSpeed Force du vent en pourcentage
    /// \param timeLeft Temps restant a la phase de construction.
    void loadHUDTexture(unsigned int powerCount, unsigned int simCoinCount, unsigned int temperatureC, unsigned int sunPower, unsigned int windSpeed, unsigned int timeLeft){
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        //Boutons

        buttonMap["skipturn"] = new Button (0, 0, 0.1, 175, 60,ResourceManager::getInstance()->getTexture("skipTurn"));
        buttonMap["structure"] = new Button (0, 630, 0.1, 90, 90, ResourceManager::getInstance()->getTexture("structure"));
        buttonMap["machine"] = new Button (90, 630, 0.1, 90, 90,ResourceManager::getInstance()->getTexture("machine"));
        buttonMap["cablage"] = new Button (180, 630, 0.1, 90, 90,ResourceManager::getInstance()->getTexture("wire"));
        buttonMap["info"] = new Button (270, 630, 0.1, 90, 90,ResourceManager::getInstance()->getTexture("info"));
        buttonMap["delete"] = new Button (360, 630, 0.1, 90, 90, ResourceManager::getInstance()->getTexture("delete"));

        ResourceManager::getInstance()->addResource("ButtonSkipTurn", buttonMap["skipturn"]);
        ResourceManager::getInstance()->addResource("ButtonStructure", buttonMap["structure"]);
        ResourceManager::getInstance()->addResource("ButtonMachine", buttonMap["machine"]);
        ResourceManager::getInstance()->addResource("ButtonCablage", buttonMap["cablage"]);
        ResourceManager::getInstance()->addResource("ButtonInfo", buttonMap["info"]);
        ResourceManager::getInstance()->addResource("ButtonDelete", buttonMap["delete"]);


        //buttonMap["skipturn"]->onClick = [this]() {actionQueue->push(new Build(0.0,std::rand() % 50,-5.0)); };
        buttonMap["structure"]->onClick = [this]() { isConstructingFondation = !isConstructingFondation; };
        //buttonMap["machine"]->onClick = [this]() { InsertMethod; };
        //buttonMap["cablage"]->onClick = [this]() { InsertMethod; };
        //buttonMap["info"]->onClick = [this]() { InsertMethod; };
        //buttonMap["delete"]->onClick = [this]() { InsertMethod; };


        //Image2D
        logoList.push_back(new Image(175, 0, 0.1, 540, 60, ResourceManager::getInstance()->getTexture("topBar")));

        //Label
        auto strSimCoin = std::to_string(simCoinCount); // transforme unsigned int en string
        labelMap["simCoins"] = new Label(fontArial->getFont(),{0,165,255}, strSimCoin, 405, 0, 0.1, 40, 35);

        auto strPwr = std::to_string(powerCount);
        labelMap["power"] = new Label(fontArial->getFont(), {255,191,0}, strPwr, 405, 30, 0.1 , 40, 35);

        auto strTime = std::to_string(timeLeft);
        strTime.push_back(' ');
        strTime.push_back('s');
        labelMap["time"] = new Label(fontArial->getFont(), {255,255,255}, strTime, 240, 0, 0.1 , 40, 60);

        auto strWind = std::to_string(windSpeed);
        strWind.push_back(' ');
        strWind.push_back('m');
        strWind.push_back('/');
        strWind.push_back('s');
        labelMap["windSpeed"] = new Label(fontArial->getFont(), {255,255,255}, strWind, 555, 15, 0.1 , 80, 35);

        auto strTemperature = std::to_string(temperatureC);
        strTemperature.push_back('c');
        labelMap["temperature"] = new Label(fontArial->getFont(), {255,255,255}, strTemperature, 685, 5, 0.1 , 20, 20);

        auto strSunPower = std::to_string(sunPower);
        strSunPower.push_back('%');
        labelMap["sun"] = new Label(fontArial->getFont(), {255,255,255}, strSunPower, 685, 37, 0.1 , 25, 20);
    }


    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if(!observables[SDL_MOUSEBUTTONDOWN])
            observables[SDL_MOUSEBUTTONDOWN]= new Observable<SDL_Event*>;
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonSkipTurn"));
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonStructure"));
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonMachine"));
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonCablage"));
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonInfo"));
        observables[SDL_MOUSEBUTTONDOWN]->subscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonDelete"));

    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonSkipTurn"));
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonStructure"));
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonMachine"));
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonCablage"));
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonInfo"));
        observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(ResourceManager::getInstance()->getResource<Button*>("ButtonDelete"));

    }

    /// Affiche les intemperies a venir.
    /// \param listeAlertes Liste de caractere representant des intemperies
    void updateAlerts(std::list<char> listeAlertes){
        if(alertsList.size() >= 1)
            for (auto it : alertsList) {
                delete(it);
            }

        unsigned int alertCount = -1;
        for (auto it : listeAlertes) {
            ++alertCount;
            if(alertCount < 7) //Affiche les alertes dans la colonne de gauche
                switch (it){
                    case 'p'://pluie/acide
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'n'://neige/acide
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'm'://meteorite/grele
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'v'://vent/tornade
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'f'://feu
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 't'://temperature
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'e'://eclair
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60,ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 's'://seisme
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'r'://radiation
                        alertsList.push_back(new Image(0 ,150 + (alertCount * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    default:
                        --alertCount;
                        break;
                }
            else//affiche les alertes dans la colonne de droite
                switch (it){
                    case 'p'://pluie/acide
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    case 'n'://neige/acide
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 'm'://meteorite/grele
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 'v'://vent/tornade
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 'f'://feu
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 't'://temperature
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 'e'://eclair
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 's'://seisme
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));

                        break;

                    case 'r'://radiation
                        alertsList.push_back(new Image(60 ,150 + ((alertCount % 7) * 60), 0.1, 60, 60, ResourceManager::getInstance()->getTexture("alert")));
                        break;

                    default:
                        --alertCount;
                        break;
                }
        }
    }

    /// Met a jour le nombre d'electricite disponible.
    /// \param power nombre d'electricite disponible
    void updatePower(unsigned int power){
        auto s = std::to_string(power);
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        labelMap["power"]->updateTextTexture(s, fontArial->getFont(),{255,191,0});
    }

    /// Met a jour le nombre de SIMcoins disponibles.
    /// \param SIMcoin nombre de SIMcoins disponibles.
    void updateSIMcoin(unsigned int SIMcoin){
        auto s = std::to_string(SIMcoin);
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        labelMap["simCoins"]->updateTextTexture(s, fontArial->getFont(),{0,165,255});
    }

    /// Met a jour la temperature.
    /// \param temp La temperature actuelle.
    void updateTemperature(unsigned int temp){
        auto s = std::to_string(temp);
        s.push_back('c');
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        labelMap["temperature"]->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Met a jour la force du soleil
    /// \param sunPower La force du soleil en pourcentage
    void updateSunPower(unsigned int sunPower){
        auto s = std::to_string(sunPower);
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        labelMap["sun"]->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Met a jour la vitesse du vent
    /// \param windSpeed La vitesse du vent
    void updateWindSpeed(Vector windSpeed){
        auto s = std::to_string(windSpeed.getNorm());
        s.push_back(' ');
        s.push_back('m');
        s.push_back('/');
        s.push_back('s');
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        labelMap["windSpeed"]->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Met a jour le temps
    /// \param time Temps  afficher
    void updateTime(unsigned int time){
        auto s = std::to_string(time);
        s.push_back(' ');
        s.push_back('s');
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        labelMap["time"]->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Active/Desactive l'affichage du InGameOverlay
    void toggleHud(){
        activeHud = !activeHud;
    }

    /// Destructeur.
    ~InGameOverlay(){
        for (auto it : alertsList) {
            delete (it);
        }
        for (auto it : logoList) {
            delete (it);
        }
        for (auto it : labelMap) {
            delete (it.second);
        }
        for (auto it : buttonMap) {
            delete(it.second);
        }
        delete actionQueue;
        delete camera;

    }
    void notify(SDL_Event* sdlEvent) {
        if (isConstructingFondation){
            switch (sdlEvent->type) {
                case SDL_MOUSEBUTTONDOWN:
                    if ((sdlEvent->button.button == SDL_BUTTON_LEFT))

                    break;

            }
        }
    }
};
#endif
