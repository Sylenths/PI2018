#ifndef EOLIENNE_H
#define EOLIENNE_H
#include "PowerSource.h"
#include "includes.h"

class Eolienne : public PowerSource {
    std::map<std::string, Model*> turbineParts;
    double angle;
    double windAngle;
    Vector centerpoint;
    Vector rotationAxe;

public:
    void setturbineAngle(Vector* wind){
        // Trouver l'angle du vent
        Matrix rotationmatrix;
        double previousAngle = angle;

        if(wind->x >0) {
            double anglevalue = (wind->y / wind->y);
            windAngle = atan(anglevalue);
        } else
            windAngle = 90;

        // Trouver l'angle opposé
        angle = windAngle + 180;
        if(angle>360){
            angle -= 360;
        }

     /*   double rotationAngle = angle - previousAngle;
        rotationmatrix.loadArbitraryRotation(centerpoint,rotationAxe, rotationAngle);
        turbineParts["Head"]->transform(rotationmatrix);*/
    }

    Eolienne(Vector* wind, double producedCurrent, const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr): PowerSource(producedCurrent,name,posx,posy,posz,textureID,rotHitBox,objFile){
   // Ajout des models de l'éolienne. Pas mis car pas encore de model.
        /*  turbineParts["Foot"] = new Model("", posx, posy, posz, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj");
     turbineParts["Fan"] = new Model("", posx, posy, posz, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj");
     */
        turbineParts["Head"] = new Model("", posx, posy, posz, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj");

        // Trouver l'angle du vent
        Matrix* rotationmatrix;

        if(wind->x >0) {
            double anglevalue = (wind->y / wind->y);
            windAngle = atan(anglevalue);
        } else
            windAngle = 90;

        // Trouver l'angle opposé
        angle = windAngle + 180;
        if(angle>360){
            angle -= 360;
        }

        centerpoint.x = posx;
        centerpoint.y = posy;
        centerpoint.z = posz;
        rotationAxe.y = posy;


    }


};

#endif
