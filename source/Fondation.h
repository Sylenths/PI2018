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

    /*
    void buildFondation(Camera* camera, std::map<std::pair<int,int>, Fondation*>* fondationGrid, World* world){
        Vector front = camera->getFront();
        Vector pos = camera->getPos();
        Vector nFloor = {0.0, 2.5, 0.0};
        if (front * nFloor) {
            double ratio = -(pos.y / front.y);
            if (ratio > 0) {
                Vector intersection = (front * ratio) + pos;
                int x = round(intersection.x / 2.0);
                int z = round(intersection.z / 2.0);
                if(!(*fondationGrid)[std::make_pair(x,z)]) {
                    Fondation* fondation = new Fondation("", (double)x * 2.0, 0.0, (double)z * 2.0, false);
                    if ((*fondationGrid)[std::make_pair(x - 1, z)]){
                        if(!(*fondationGrid)[std::make_pair(x,z)])
                            (*fondationGrid)[std::make_pair(x,z)] = fondation;
                        (*fondationGrid)[std::make_pair(x,z)]->west = (*fondationGrid)[std::make_pair(x - 1, z)];
                        (*fondationGrid)[std::make_pair(x - 1, z)]->east = (*fondationGrid)[std::make_pair(x,z)];
                    }

                    if((*fondationGrid)[std::make_pair(x + 1, z)]){
                        if(!(*fondationGrid)[std::make_pair(x,z)])
                            (*fondationGrid)[std::make_pair(x,z)] = fondation;
                        (*fondationGrid)[std::make_pair(x,z)]->east = (*fondationGrid)[std::make_pair(x + 1, z)];
                        (*fondationGrid)[std::make_pair(x + 1, z)]->west = (*fondationGrid)[std::make_pair(x,z)];
                    }

                    if((*fondationGrid)[std::make_pair(x, z - 1)]){
                        if(!(*fondationGrid)[std::make_pair(x,z)])
                            (*fondationGrid)[std::make_pair(x,z)] = fondation;
                        (*fondationGrid)[std::make_pair(x,z)]->north = (*fondationGrid)[std::make_pair(x , z - 1)];
                        (*fondationGrid)[std::make_pair(x , z - 1)]->south = (*fondationGrid)[std::make_pair(x,z)];
                    }

                    if((*fondationGrid)[std::make_pair(x, z + 1)]){
                        if(!(*fondationGrid)[std::make_pair(x,z)])
                            (*fondationGrid)[std::make_pair(x,z)] = fondation;
                        (*fondationGrid)[std::make_pair(x,z)]->south = (*fondationGrid)[std::make_pair(x , z + 1)];
                        (*fondationGrid)[std::make_pair(x , z + 1)]->north = (*fondationGrid)[std::make_pair(x,z)];
                    }

                    if((*fondationGrid)[std::make_pair(x,z)])
                        world->addModel((*fondationGrid)[std::make_pair(x,z)]);
                    else
                        delete fondation;
                }

            }
        }
    }
*/

};
#endif
