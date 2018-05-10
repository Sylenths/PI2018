/// \brief Represente les murs sur les quelles les planchers et les toits vont être construit
/// \author Shelby Versailles
/// \date 10 mai 2018
/// \version 0.1
/// \warning
/// \bug Aucuns.

#ifndef SOURCE_WALL_H
#define SOURCE_WALL_H
class Wall : public Structure{
public:
    Materiel* material;
    Wall(const std::string& name, unsigned int height, unsigned int textureID, Vector* firstCorner, Vector* secondCorner, int material) : Structure(name, posx, posy, posz, textureID, rotHitBox, nullptr) {
        vertexCount = 6;
        normalCount = 6;
        texCount = 6;

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

///sommet

        vertices = new double[18];
        vertices[0] = firstCorner->x;
        vertices[1] = firstCorner->y;
        vertices[2] = firstCorner->z;
        vertices[15] = vertices[3] = firstCorner->x;
        vertices[16] = vertices[4] = firstCorner->y + height;
        vertices[17] = vertices[5] = firstCorner->z;


        vertices[9] = vertices[6] = secondCorner->x;
        vertices[10] = vertices[7] = secondCorner->y;
        vertices[11] = vertices[8] = secondCorner->z;

        vertices[12] = secondCorner->x;
        vertices[13] = secondCorner->y + height;
        vertices[14] = secondCorner->z;
///normal
        normals = new double[18];

        if(vertices[0] == vertices[3]){
            normals[0] = normals[3] = normals[6] = normals[9] = normals[12] = normals[15] = 0.0;
            normals[1] = normals[4] = normals[7] = normals[10] = normals[13] = normals[16] = 0.0;
            normals[2] = normals[5] = normals[8] = normals[11] = normals[14] = normals[17] = 1.0;
        }
        else{
            normals[0] = normals[3] = normals[6] = normals[9] = normals[12] = normals[15] = 1.0;
            normals[1] = normals[4] = normals[7] = normals[10] = normals[13] = normals[16] = 0.0;
            normals[2] = normals[5] = normals[8] = normals[11] = normals[14] = normals[17] = 0.0;
        }


///coordoné de texture
        texCoords = new double[12];
        texCoords[0] = 1.0;
        texCoords[1] = 1.0;
        texCoords[2] = 1.0;
        texCoords[3] = 0.0;
        texCoords[4] = 0.0;
        texCoords[5] = 1.0;

        texCoords[6] = 0.0;
        texCoords[7] = 1.0;
        texCoords[8] = 0.0;
        texCoords[9] = 0.0;
        texCoords[10] = 1.0;
        texCoords[11] = 0.0;
//todo hitbox
        ///hitbox
        verticesHitBox = new double[18];
        verticesHitBox[0] = firstCorner->x;
        verticesHitBox[1] = firstCorner->y;
        verticesHitBox[2] = firstCorner->z;
        verticesHitBox[15] = verticesHitBox[3] = firstCorner->x;
        verticesHitBox[16] = verticesHitBox[4] = firstCorner->y + height;
        verticesHitBox[17] = verticesHitBox[5] = firstCorner->z;


        verticesHitBox[9] = verticesHitBox[6] = secondCorner->x;
        verticesHitBox[10] = verticesHitBox[7] = secondCorner->y;
        verticesHitBox[11] = verticesHitBox[8] = secondCorner->z;

        verticesHitBox[12] = secondCorner->x;
        verticesHitBox[13] = secondCorner->y + height;
        verticesHitBox[14] = secondCorner->z;
///normal
        normalsHitBox = new double[18];

        if(verticesHitBox[0] == verticesHitBox[3]){
            normalsHitBox[0] = normalsHitBox[3] = normalsHitBox[6] = normalsHitBox[9] = normalsHitBox[12] = normalsHitBox[15] = 0.0;
            normalsHitBox[1] = normalsHitBox[4] = normalsHitBox[7] = normalsHitBox[10] = normalsHitBox[13] = normalsHitBox[16] = 0.0;
            normalsHitBox[2] = normalsHitBox[5] = normalsHitBox[8] = normalsHitBox[11] = normalsHitBox[14] = normalsHitBox[17] = 1.0;
        }
        else{
            normalsHitBox[0] = normalsHitBox[3] = normalsHitBox[6] = normalsHitBox[9] = normalsHitBox[12] = normalsHitBox[15] = 1.0;
            normalsHitBox[1] = normalsHitBox[4] = normalsHitBox[7] = normalsHitBox[10] = normalsHitBox[13] = normalsHitBox[16] = 0.0;
            normalsHitBox[2] = normalsHitBox[5] = normalsHitBox[8] = normalsHitBox[11] = normalsHitBox[14] = normalsHitBox[17] = 0.0;
        }
    }

};
#endif
