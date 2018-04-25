/// \brief Représentation de l'interface en jeu.
/// \details Interface pour construire et pour donner les informations sur la partie.
/// \author Antoine Legault , Guillaume Julien - Desmarchais, Mickaël Grisé-Roy
/// \date 24 mars 2018
/// \version 0.7
/// \warning Manque la boussole (pour indiquer le sens du vent) et le compte a rebours. Les labels ne s'ajuste pas selon la grosseur du nombre.
/// \bug Problemes avec le sideWindow , fonctionne à 90%
#ifndef SOURCE_INGAMEOVERLAY_H
#define SOURCE_INGAMEOVERLAY_H


#include "includes.h"
#include <queue>
#include "Menu.h"
#include "Action.h"
#include "Build.h"

#include "SideWindow.h"
#include "DeleteWindow.h"
#include "StructureWindow.h"
#include "ProjetFinal.h"
#include "WireWindow.h"
#include "MachineWindow.h"
#include "InformationWindow.h"

class InGameOverlay : public Menu{
private:
    bool activeHud;///< Bool qui determine si le hud est affiché
    Camera* camera;
    std::map<std::pair<int,int>, Fondation*> fondationGrid;///< Map Qui prend une clé de pair qui sont les 2 coordonnées en x et z des fondations qui seront crées.
    std::list<Image*> alertsList;///< Liste alerte annoncant les intempéries a venir
    std::list<Image*> logoList;///< Liste d'image contenant les logo a afficher
    std::queue<Action*>* actionQueue;///< File contenant les actions a faire (Build, Delete, etc)
    SideWindow* sideWindow; ///< Pointe la fenêtre de coté active
    std::map<std::string, SideWindow*> sideWindowMap; ///< Carte de sideWindow
    //RotatingImage* windIndicator;

public:
    bool isConstructingFondation;

    /// Constructeur.
    /// \param powerCount Nombre d'électricité disponible.
    /// \param simCoinCount Nombre de SIMcoins disponible
    /// \param temperatureC La température en celsius
    /// \param sunPower Puissance du soleil en pourcentage
    /// \param windSpeed Force du vent en pourcentage
    /// \param timeLeft Temps restant à la phase de construction.
    InGameOverlay(unsigned int powerCount = 0, unsigned int simCoinCount = 0, unsigned int temperatureC = 0, unsigned int sunPower = 0, Vector windSpeed = {0, 0, 0}, unsigned int timeLeft = 0) {
        activeHud = true;
        fondationGrid[std::make_pair(0,0)]= new Fondation(0,0,0,false);
        loadHUDTexture(powerCount, simCoinCount, temperatureC, sunPower, windSpeed.getNorm(), timeLeft);
        actionQueue = new std::queue<Action*>;
        isConstructingFondation = false;
        sideWindowMap["Delete"] = new DeleteWindow();
        sideWindowMap["Structure"] = new StructureWindow();
        sideWindowMap["Wire"] = new WireWindow();
        sideWindowMap["Machine"] = new MachineWindow();
        sideWindowMap["Information"] = new InformationWindow();
        sideWindow = sideWindowMap["Nothing"];
        camera = new Camera({ 10.0, 3.5, 10.0 }, { 0.0, 3.5, 0.0 }, { 0.0, 1.0, 0.0 });
        camera->loadViewMatrix();
    }

    std::queue<Action*>* getActions(){
            return actionQueue;
    }
    Camera* getCamera(){
        return camera;
    }
    std::map<std::pair<int,int>, Fondation*>* getFondations (){
        return &fondationGrid;
    };

    /// Affiche le InGameOverlay.
    void draw(){
        if(activeHud) {

            for (auto it : logoList) {
                it->draw();
            }
            for (auto it : alertsList) {
                it->draw();
            }
            for (auto it : models) {
                it.second->draw();
            }
            if(sideWindow != sideWindowMap["Nothing"])
                sideWindow->draw();
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
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial30");

        models["skipturn"] = new Button (0, 0, 0.1, 175, 60,ResourceManager::getInstance()->getTexture("skipTurn"));
        models["skipturn"]->onClick = [this]() {isConstructingFondation = !isConstructingFondation; };

        models["structure"] = new Button (0, 630, 0.1, 90, 90, ResourceManager::getInstance()->getTexture("structure"));
        models["structure"]->onClick = [this]() { activeStructureSideWindow(); };

        models["machine"] = new Button (90, 630, 0.1, 90, 90,ResourceManager::getInstance()->getTexture("machine"));
        models["machine"]->onClick = [this]() { activeMachineSideWindow(); };

        models["cablage"] = new Button (180, 630, 0.1, 90, 90,ResourceManager::getInstance()->getTexture("wire"));
        models["cablage"]->onClick = [this]() { activeWireSideWindow(); };

        models["info"] = new Button (270, 630, 0.1, 90, 90,ResourceManager::getInstance()->getTexture("info"));
        models["info"]->onClick = [this]() { activeInfoSideWindow(); };

        models["delete"] = new Button (360, 630, 0.1, 90, 90, ResourceManager::getInstance()->getTexture("delete"));
        models["delete"]->onClick = [this]() { activeDeleteSideWindow(); };


        //Image2D
        logoList.push_back(new Image(175, 0, 0.1, 540, 60, ResourceManager::getInstance()->getTexture("topBar")));

        //Label
        auto strSimCoin = std::to_string(simCoinCount); // transforme unsigned int en string
        models["simCoins"] = new Label(fontArial->getFont(),{0,165,255}, strSimCoin, 405, 0, 0.1);

        auto strPwr = std::to_string(powerCount);
        models["power"] = new Label(fontArial->getFont(), {255,191,0}, strPwr, 405, 30, 0.1);

        auto strTime = std::to_string(timeLeft);
        strTime.push_back(' ');
        strTime.push_back('s');
        models["time"] = new Label(fontArial->getFont(), {255,255,255}, strTime, 240, 0, 0.1);

        auto strWind = std::to_string(windSpeed);
        strWind.push_back(' ');
        strWind.push_back('m');
        strWind.push_back('/');
        strWind.push_back('s');
        models["windSpeed"] = new Label(fontArial->getFont(), {255,255,255}, strWind, 555, 15, 0.1);

        auto strTemperature = std::to_string(temperatureC);
        strTemperature.push_back('c');
        models["temperature"] = new Label(fontArial->getFont(), {255,255,255}, strTemperature, 685, 5, 0.1);

        auto strSunPower = std::to_string(sunPower);
        strSunPower.push_back('%');
        models["sun"] = new Label(fontArial->getFont(), {255,255,255}, strSunPower, 685, 37, 0.1);
    }


    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : models) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : models) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);
        }

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
        ((Label*)models["power"])->updateTextTexture(s, fontArial->getFont(),{255,191,0});
    }

    /// Met a jour le nombre de SIMcoins disponibles.
    /// \param SIMcoin nombre de SIMcoins disponibles.
    void updateSIMcoin(unsigned int SIMcoin){
        auto s = std::to_string(SIMcoin);
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        ((Label*)models["simCoins"])->updateTextTexture(s, fontArial->getFont(),{0,165,255});
    }

    /// Met a jour la temperature.
    /// \param temp La temperature actuelle.
    void updateTemperature(unsigned int temp){
        auto s = std::to_string(temp);
        s.push_back('c');
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        ((Label*)models["temperature"])->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Met a jour la force du soleil
    /// \param sunPower La force du soleil en pourcentage
    void updateSunPower(unsigned int sunPower){
        auto s = std::to_string(sunPower);
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        ((Label*)models["sun"])->updateTextTexture(s, fontArial->getFont(),{255,255,255});
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
        ((Label*)models["windSpeed"])->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Met a jour le temps
    /// \param time Temps  afficher
    void updateTime(unsigned int time){
        auto s = std::to_string(time);
        s.push_back(' ');
        s.push_back('s');
        Font* fontArial = ResourceManager::getInstance()->getResource<Font*>("font - arial12");
        ((Label*)models["time"])->updateTextTexture(s, fontArial->getFont(),{255,255,255});
    }

    /// Active/Desactive l'affichage du InGameOverlay
    void toggleHud(){
        activeHud = !activeHud;
    }

    /// Active la fenêtre de construction de structure
    void activeStructureSideWindow(){
        if(sideWindow != sideWindowMap["Structure"]){
            sideWindow = sideWindowMap["Structure"];
        }
        else
            sideWindow = sideWindowMap["Nothing"];
        // TODO: Code Structure mode
        sceneChange = true;
        isConstructingFondation = !isConstructingFondation;

    }

    /// Active la fenêtre de construction de machine
    void activeMachineSideWindow(){
        if(sideWindow != sideWindowMap["Machine"])
            sideWindow = sideWindowMap["Machine"];
        else
            sideWindow = sideWindowMap["Nothing"];
        sceneChange = true;

        // TODO: Code delete mode
    }

    /// Active la fenêtre de construction de cable
    void activeWireSideWindow(){
        if(sideWindow != sideWindowMap["Wire"])
            sideWindow = sideWindowMap["Wire"];
        else
            sideWindow = sideWindowMap["Nothing"];
        sceneChange = true;


        // TODO: Code Wire mode
    }
    /// Active la fenêtre d'information
    void activeInfoSideWindow(){
        if(sideWindow != sideWindowMap["Information"])
            sideWindow = sideWindowMap["Information"];
        else
            sideWindow = sideWindowMap["Nothing"];
        sceneChange = true;

        // TODO: Code Info mode

    }
    /// Active la fenêtre de destruction
    void activeDeleteSideWindow(){
        if(sideWindow != sideWindowMap["Delete"])
            sideWindow = sideWindowMap["Delete"];
        else
            sideWindow = sideWindowMap["Nothing"];
        sceneChange = true;

        // TODO: Code delete mode
    }

    void cancelButton(){

    }


    void sideWndowSubscribe( std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if(sideWindow != sideWindowMap["Nothing"])
            sideWindow->subscribeAll(observables);
    }

    void sideWindowUnsubscribe( std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if(sideWindow != sideWindowMap["Nothing"])
            sideWindow->unsubscribeAll(observables);
    }

    /// Destructeur.
    ~InGameOverlay(){
        for (auto it : alertsList) {
            delete (it);
        }
        for (auto it : logoList) {
            delete (it);
        }
        for (auto it : sideWindowMap)
            delete it.second;

        //delete sideWindow;
        delete actionQueue;
        delete camera;

    }

};
#endif
