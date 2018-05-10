/// \brief Classe qui représentera l'éolienne.
/// \details L'éolienne permettra de générer de l'énergie dans le jeu. Fonctionnera selon les principes physiques propres aux éoliennes.
/// \author Jade St-Pierre Bouchard
/// \date 10 mai 2010
/// \version 0.1
/// \warnings Ne pas mettre de longueur négative.
/// \bugs Aucuns.

#ifndef EOLIENNE_H
#define EOLIENNE_H
#include "PowerSource.h"
#include "includes.h"
#include "MathUtils.h"

class Eolienne : public PowerSource {
    std::map<std::string, Model*> turbineParts;
    double angle;
    double windAngle;
    double power;
    double temperature;
    double windSpeed;
    double paleLength;
    double turbineSpeed;
    double paleMasse;

    Vector centerpoint;
    Vector rotationAxe;

    /// Production d'énergie par seconde.
    void setTurbinePower(){
        double windPower;
        if(windSpeed>= 4){
            windPower = .5*masseVolumiqueAirEnFonctionDeTemperature(temperature)*(MATH_PI*pow(paleLength,2))*pow(windSpeed,3);
            power = (55/100)*windPower;
        }
        else {
            power = 0.0;
        }

    }

    /// Calcule la masse des pales de l'eolienne en fonction de leur longueur.
    void setPaleMasse(){
        // Règle de 4 : pour une pale de 41m2 elle pèse 6500 kg.
        paleMasse = ((paleLength*6500)/41);
    }

    /// Ajuste la vitesse de l'eolienne.
    void setTurbineSpeed(){
        turbineSpeed = sqrt((2*power)/paleMasse);
    }
public:
    /// Calcul l'angle de provenance du vent.
    /// \param wind Vecteur représentant la direction du vent.
    double getWindAngle(Vector* wind){
        if(wind->x >0) {
            double anglevalue = (wind->y / wind->y);
            windAngle = atan(anglevalue);
        } else
        windAngle = 90;

    }
    /// Oriente l'eolienne dans la bonne direction.
    /// \param wind vecteur représentant la direction du vent.
    void setTurbineAngle(Vector* wind){
        // Trouver l'angle du vent
        Matrix rotationmatrix;
        double previousAngle = angle;

        getWindAngle(wind);
        // Trouver l'angle opposé
        angle = windAngle + 180;
        if(angle>360){
            angle -= 360;
        }

        double rotationAngle = angle - previousAngle;
        rotationmatrix.loadArbitraryRotation(centerpoint,rotationAxe, rotationAngle);
        turbineParts["Head"]->transform(rotationmatrix);
    }

    Eolienne(Vector* wind,double windSpeed,double temperature, double producedCurrent, const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr, double paleLength = 2): PowerSource(producedCurrent,name,posx,posy,posz,textureID,rotHitBox,objFile){
   // Ajout des models de l'éolienne. Pas mis car pas encore de model.
     /*
      * turbineParts["Foot"] = new Model("", posx, posy, posz, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj");
      * turbineParts["Fan"] = new Model("", posx, posy, posz, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj");
     */
        turbineParts["Head"] = new Model("", posx, posy, posz, EntityManager::get<Texture2d*>("bambou")->ID,false, "../../models/obj/tree2.0.obj");

        centerpoint.x = posx;
        centerpoint.y = posy;
        centerpoint.z = posz;
        rotationAxe.y = posy;

        setTurbineAngle(wind);
        this->windSpeed = windSpeed;
        this->temperature = temperature;
        this->paleLength = paleLength;
        setPaleMasse();


    }



};

#endif
