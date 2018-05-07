//
// Created by Mic on 2018-05-01.
//

#ifndef SOURCE_FLOOR_H
#define SOURCE_FLOOR_H

class Floor : public Structure{
public:
    Vector* centerPoint;
    Floor* north;
    Floor* south;
    Floor* east;
    Floor* west;

    Floor(double posx, double posy, double posz, bool rotHitBox,  unsigned int textureID = ResourceManager::getTexture("fondation"), const char* objFile = "../../models/obj/fondation.obj") : Structure( posx, posy, posz, textureID, rotHitBox, objFile){
        north = south = east = west = nullptr;
        centerPoint = new Vector(posx,posy,posz);
    }
};
#endif //SOURCE_FLOOR_H
