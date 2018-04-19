/// \brief Reprsentation du monde et de la partie
/// \details Contient les donnes de jeux, methodes et models pour la partie
/// \author Mickaël Grisé-Roy, Gabriel Bourdages
/// \date 2 Avril 2018
/// \version 0.1

#ifndef SOURCE_WORLD_H
#define SOURCE_WORLD_H

#include "includes.h"
#include "GLContext.h"
#include "Camera.h"
#include "Sky.h"
#include "Atmosphere.h"
#include "Build.h"
#include "BuildWall.h"
class World : public Scene{
private:
    std::list<Model*> modelList; ///< La liste de models à afficher
    Sky sky;
    Atmosphere atmosphere;
    Vector wind;
    unsigned int temperature, simCoin, totalPower, usedPower, sunPower, elapsedTime, buildingTime;
    Light* worldLight, * hudLight;
    Matrix fanRotationMatrix;
    Chrono chrono;

public:
    Model* floor;
    InGameOverlay* hud;

    int test = 0;
    /// Ajoute un model a afficher
    /// \param model le model a ajouter
    /// \param modelKey Nom donne au model
    void addModel(Model* model){
        modelList.push_back(model);
    }

    /// Constructeur, tout les models nécéssaires sont loadés ici.
    World(unsigned int temperature, unsigned int sunPower, unsigned int simCoin, unsigned int buildingTime, Vector wind) : sky(0.0, 0.0, 0.0, false, ResourceManager::getInstance()->getTexture("daysky")), atmosphere(0.0, 0.0, 0.0, false, 0) {
        this->wind = wind;
        this->temperature = temperature;
        this->sunPower = sunPower;
        this->simCoin = simCoin;
        this->buildingTime = buildingTime;
        totalPower = 0;
        usedPower = 0;
        elapsedTime = 0;
        hud = new InGameOverlay(0, simCoin, temperature, sunPower, wind, 0);
        addModel((*hud->getFondations())[std::make_pair(0,0)]);
        floor =  new Model(0.0, 0.0, 0.0, ResourceManager::getInstance()->getTexture("grass"), false, "../../models/obj/grass.obj");
        addModel(floor);
        addModel(new Sky(0.0, 0.0, 0.0, ResourceManager::getInstance()->getTexture("daysky"),false, "../../models/obj/skysphere.obj"));
        addModel(new Model(0.0, 1.0, -1.0, ResourceManager::getInstance()->getTexture("fan"), true, "../../models/obj/fan.obj"));
	    addModel(new Model(0.0, 0.0, 2.0, ResourceManager::getInstance()->getTexture("simcoinminer"), true, "../../models/obj/simcoin_miner.obj"));
	    addModel(new Model(0.0, 0.0, -2.0, ResourceManager::getInstance()->getTexture("human"), true, "../../models/obj/human.obj"));


        worldLight = new Light(0.0, 25.0, 0.0, 4.0);
        hudLight = new Light(0.0, 0.0, 1.0, 0.0);



        chrono.restart();
    }
    ~World(){
        delete hud;
        delete worldLight;
        delete hudLight;
    }

    void checkForActions(){

        while(!hud->getActions()->empty()){
            switch (hud->getActions()->front()->getActionType()){
                case BUILD:/* double x = ((Build*)hud->getActions()->front())->x;
                            double y = ((Build*)hud->getActions()->front())->y;
                            double z = ((Build*)hud->getActions()->front())->z;
                            addModel(new Model(x,y,z,false,ResourceManager::getInstance()->getTexture("human"),"../../models/obj/human.obj"));
                            delete hud->getActions()->front();*/
                    switch(/*((Build*)hud->getActions()->front())->buildType*/ test) {
                        case 2:
                            test = 0;
                            Fondation *start = ((BuildWall *) hud->getActions()->front())->getFondation();
                            while (start->north) {
                                start = start->north;
                            }
                            Fondation *previousPosition = start;
                            Fondation *currentPosition;
                            Fondation *switchVariable;
                            std::list<Vector> corner;

                            if (previousPosition->east) {
                                currentPosition = previousPosition->east;
                            } else {
                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, -1.0});
                                if (previousPosition->west) {
                                    currentPosition = previousPosition->west;
                                } else {
                                    corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, -1.0});
                                    if (previousPosition->south) {
                                        currentPosition = previousPosition->south;
                                    } else {
                                        currentPosition = previousPosition;
                                        corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, 1.0});
                                        corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, 1.0});
                                    }
                                }
                            }

                            while (start != currentPosition) {

                                ///deplace vers le nord et regarde a l'oest
                                if (currentPosition == previousPosition->north) {
                                    if (!currentPosition->west) {
                                        if (currentPosition->north) {
                                            previousPosition = currentPosition;
                                            currentPosition = currentPosition->north;
                                        } else {
                                            if (currentPosition->east) {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->east;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, 1.0});
                                            } else {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->south;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, -1.0});
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, -1.0});
                                            }
                                        }
                                    } else {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->west;
                                        corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, 1.0});
                                    }
                                }

                                ///deplace vers l'est et regarde a le nord
                                if (currentPosition == previousPosition->east) {
                                    if (!currentPosition->north) {
                                        if (currentPosition->east) {
                                            previousPosition = currentPosition;
                                            currentPosition = currentPosition->east;
                                        } else {
                                            if (currentPosition->south) {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->south;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, 1.0});
                                            } else {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->west;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, -1.0});
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, 1.0});
                                            }
                                        }
                                    } else {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->north;
                                        corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, 1.0});
                                    }

                                }

                                ///deplace vers le sud et regarde a l'est
                                if (currentPosition == previousPosition->south) {
                                    if (!currentPosition->east) {
                                        if (currentPosition->south) {
                                            previousPosition = currentPosition;
                                            currentPosition = currentPosition->south;
                                        } else {
                                            if (currentPosition->west) {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->west;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, -1.0});
                                            } else {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->north;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, 1.0});
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){-1.0, 0.0, 1.0});
                                            }
                                        }
                                    } else {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->east;
                                        corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, -1.0});
                                    }

                                }

                                ///deplace vers l'oest et regarde a le sud
                                if (currentPosition == previousPosition->west) {

                                    if (!currentPosition->south) {
                                        if (currentPosition->west) {
                                            previousPosition = currentPosition;
                                            currentPosition = currentPosition->west;
                                        } else {
                                            if (currentPosition->north) {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->north;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, -1.0});
                                            } else {
                                                previousPosition = currentPosition;
                                                currentPosition = currentPosition->east;
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, -1.0});
                                                corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, 1.0});
                                            }
                                        }
                                    } else {
                                        previousPosition = currentPosition;
                                        currentPosition = currentPosition->south;
                                        corner.push_back((*previousPosition->centerPoint) + (Vector){1.0, 0.0, 1.0});
                                    }

                                }

                            }
                            for (int i = 0; i < corner.size(); ++i) {
                                Vector temp = corner.front();
                                corner.pop_front();
                                addModel(new Model(/*((BuildWall *) hud->getActions()->front())->getHeight()*/ 1., /*((BuildWall *) hud->getActions()->front())->getMateriel()->getTextureID()*/ 5, &temp, &corner.front()));
                            }

                            break;
                    }


                    hud->getActions()->pop();
                    break;
            }
        }
    }

    /// Affichage des models
    void draw() {
        checkForActions();
        GLContext::setFrustum(IS3D);


        sky.update(chrono);
        if(sky.getTime())
            atmosphere.darken(chrono);
        else
            atmosphere.lighten(chrono);

        hud->getCamera()->applyViewMatrix();
        worldLight->applyLightPosition();
        for(auto it = modelList.begin(); it != modelList.end(); it++)
            (*it)->draw();
       // for(auto it = hud->getFondations()->begin(); it != hud->getFondations()->end(); it++)
            //(*it).second->draw();
        GLContext::setFrustum(IS2D);
        hudLight->applyLightPosition();
        hud->draw();

    }

    /// Mise a jour du temps dans l'H.U.D.
    /// \param chrono Chrono qui calcul le temps restant
    void updateTimeLeft(Chrono* chrono) {
       hud->updateTime(buildingTime - chrono->getElapsed(SECONDS));
    }

    void buildingPhaseStart() {

    }

    void buildingPhaseStop() {

    }

    void catastrophePhaseStart() {

    }

    void catastrophePhaseStop() {

    }
    Camera* getCamera(){
        return hud->getCamera();
    }

    virtual void subscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();
        if (!observables[SDL_KEYDOWN]) observables[SDL_KEYDOWN] = new Observable<SDL_Event*>();
        hud->subscribeAll(observables);

    }
    virtual void unsubscribeAll( std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        hud->unsubscribeAll(observables);

    }

    InGameOverlay* getHud(){
        return hud;
    }


};
#endif //SOURCE_WORLD_H
