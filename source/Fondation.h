/// \brief Represente les fondation sur les quelles les mur vont être construit
/// \author Shelby Versailles
/// \date 17 avril 2018
/// \version 0.1
/// \warning N'est pas complet manque ce qu'il faut lors de la création de la fondation.
/// \bug Aucuns.
#ifndef SOURCE_FONDATION_H
#define SOURCE_FONDATION_H

class Fondation : public Structure{
private:
    bool isOccupied;
public:
    Materiel* material;
    Vector* centerPoint;
    Fondation* north;
    Fondation* south;
    Fondation* east;
    Fondation* west;

    Fondation(const std::string name, double posx, double posy, double posz, bool rotHitBox,  unsigned int textureID = EntityManager::get<Texture2d*>("fondation")->ID, const char* objFile = "../../models/obj/fondation.obj") : Structure(name, posx, posy, posz, textureID, rotHitBox, objFile){
        north = south = east = west = nullptr;
        centerPoint = new Vector(posx,posy,posz);
        isOccupied = false;

    }

    void setFondationOccupied(){
        isOccupied = true;
    }

    bool getOccupiedState(){
        return isOccupied;
    }
};
#endif //SOURCE_FONDATION_H
