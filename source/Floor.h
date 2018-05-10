//
// Created by Mic on 2018-05-01.
//

#ifndef SOURCE_FLOOR_H
#define SOURCE_FLOOR_H

class Floor : public Structure{
public:
    Vector* centerPoint;
    Floor* north,
         * south,
         * east,
         * west;

    Floor(const std::string name, double posx, double posy, double posz, bool rotHitBox,  unsigned int textureID = EntityManager::get<Texture2d*>("fondation")->ID, const char* objFile = "../../models/obj/fondation.obj") : Structure(name, posx, posy, posz, textureID, rotHitBox, objFile){
        north = south = east = west = nullptr;
        centerPoint = new Vector(posx,posy,posz);
    }
};
#endif //SOURCE_FLOOR_H
