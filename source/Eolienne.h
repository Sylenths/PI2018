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
#include "ProjetFinal.h"

#define FOOT 0
#define HEAD 1
#define PROPELLER 2

class Eolienne : public PowerSource {
    Model* turbineParts[3];
    double angle, windAngle, power, temperature, windSpeed, paleLength, turbineSpeed, paleMasse;
    Vector centerpoint, rotationAxe;

    /// Production d'énergie par seconde.
    void setTurbinePower(){
        double windPower;
        if(windSpeed>= 4.0){
            windPower = 0.5 * masseVolumiqueAirEnFonctionDeTemperature(temperature)*(MATH_PI*pow(paleLength,2))*pow(windSpeed,3);
            power = (55 / 100) * windPower;
        }
        else
            power = 0.0;
    }

    /// Calcule la masse des pales de l'eolienne en fonction de leur longueur.
    void setPaleMasse(){
        // Règle de 4 : pour une pale de 41m2 elle pèse 6500 kg.
        paleMasse = ((paleLength * 6500.0) / 41.0);
    }

    /// Ajuste la vitesse de l'eolienne.
    void setTurbineSpeed(){
        turbineSpeed = sqrt((2.0 * power) / paleMasse);
    }
public:
    /// Calcul l'angle de provenance du vent.
    /// \param wind Vecteur représentant la direction du vent.
    double getWindAngle(Vector* wind){
        if(wind->x > 0.0) {
            double anglevalue = (wind->y / wind->y);
            windAngle = atan(anglevalue);
        } else
            windAngle = 90.0;

    }
    /// Oriente l'eolienne dans la bonne direction.
    /// \param wind vecteur représentant la direction du vent.
    void moveTurbine(Vector* wind, Chrono chrono){
        // Trouver l'angle du vent
        Matrix rotationmatrix;
        rotationmatrix.loadArbitraryRotation(centerpoint,centerpoint.x,(.1*10));
        turbineParts[PROPELLER]->transform(rotationmatrix);

    }
    void modifyTurbineAngle(Vector* wind){
        Matrix rotationmatrix;
        double previousAngle = angle;

        getWindAngle(wind);
        angle = (double)((int)(windAngle + 180) % 360);

        double rotationAngle = angle - previousAngle;
         rotationmatrix.loadArbitraryRotation(centerpoint,{0,1,0},90);
         turbineParts[HEAD]->transform(rotationmatrix);

        centerpoint.x += 0.86729;
         rotationmatrix.loadArbitraryRotation(centerpoint,{0,1,0},90);
         turbineParts[PROPELLER]->transform(rotationmatrix);
    }

    Eolienne(Vector* wind,double windSpeed,double temperature, double producedCurrent, const std::string& name, double posx, double posy, double posz, bool rotHitBox, const char* objFile = nullptr, double paleLength = 2): PowerSource(producedCurrent,name,posx,posy,posz, 0,rotHitBox,objFile) {
        turbineParts[FOOT] = new Model("mdlWindTurbineFoot", posx, posy, posz, EntityManager::get<Texture2d*>("txtrWindTurbineFoot")->ID, false, "../../models/obj/windTurbineFoot.obj");
        turbineParts[HEAD] = new Model("mdlWindTurbineHead", posx, posy, posz, EntityManager::get<Texture2d*>("txtrWindTurbineHead")->ID, false, "../../models/obj/windTurbineHead.obj");
        turbineParts[PROPELLER] = new Model("mdlWindTurbinePropeller", posx, posy, posz, EntityManager::get<Texture2d*>("txtrWindTurbinePropeller")->ID, false, "../../models/obj/windTurbinePropeller.obj");

        centerpoint.x = posx;
        centerpoint.y = posy + 5.18;
        centerpoint.z = posz;


        //setTurbineAngle(wind);
        this->windSpeed = windSpeed;
        this->temperature = temperature;
        this->paleLength = paleLength;
        setPaleMasse();
    }

    void draw() {
        turbineParts[FOOT]->draw();
        turbineParts[HEAD]->draw();
        turbineParts[PROPELLER]->draw();
    }
};

#endif
