//
// Created by Mic on 2018-05-01.
//

#ifndef SOURCE_FLOOR_H
#define SOURCE_FLOOR_H

class Floor : public Structure{
private:
    double realWeight;
public:
    Vector* centerPoint;
    Floor* north,
         * south,
         * east,
         * west;
    double weight;
    double forceApplied;
    Materiel* material;

    Floor(const std::string name, double posx, double posy, double posz, bool rotHitBox,  unsigned int textureID, int material, const char* objFile = "../../models/obj/fondation.obj") : Structure(name, posx, posy, posz, textureID, rotHitBox, objFile){
        north = south = east = west = nullptr;
        centerPoint = new Vector(posx,posy,posz);
        switch(material){
            case WOOD:
                this->material = Materiel::bois;
                break;
            case CARDBOARD:
                this->material = Materiel::carton;
                break;
            case ROCK:
                this->material = Materiel::pierre;
                break;
            case METAL:
                this->material = Materiel::metal;
                break;
            case SIMTIUM:
                this->material = Materiel::simtium;
                break;
        }

        forceApplied = 0.0;
        weight = 1.0 * this->material->masse * 9.8;
    }
    double getRealWeight(){
        return realWeight;
    }
};
#endif //SOURCE_FLOOR_H
