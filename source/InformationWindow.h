/// \brief Représentation de la fenêtre d'information
/// \details Donne l'information des objets cliqués.
/// \author Guillaume Julien - Desmarchais
/// \date 20 mars 2018
/// \version 0.1
/// \warning Aucun
/// \bug Aucun
#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H
class InformationWindow : public SideWindow{
public:

    InformationWindow(){
        modelsSideWindow["SideMenuInformation"] = new Image(920, 0, 0, 360, 720, ResourceManager::getInstance()->getTexture("InformationWindow"));
    }

    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
    }

    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables){
        for (auto it : modelsSideWindow) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);
        }

    }

};
#endif //INFORMATIONWINDOW_H
