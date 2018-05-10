/// \brief Represente les toits
/// \author Shelby Versailles
/// \date 10 mai 2018
/// \version 0.1
/// \warning
/// \bug Aucuns.
#ifndef SOURCE_ROOF_H
#define SOURCE_ROOF_H
class Roof : public Structure{
private:
    double realWeight;
public:
    double weight;
    double forceApplied;
    Materiel* material;
    Roof(const std::string& name, unsigned int width, unsigned int height, unsigned int lenght, double posx, double posy, double posz, unsigned int textureID, int material) : Structure(name, posx, posy, posz, textureID, rotHitBox, nullptr) {

            Vector up;
            Vector temp;
            vertexCount = 12;
            normalCount = 12;
            texCount = 12;

            forceApplied = 0.0;

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
        realWeight = ((double)width * sqrt((double)lenght * (double)lenght * (double)height * (double)height)) + ((double)lenght * sqrt((double)width * (double)width * (double)height * (double)height)) * this->material->masse * GRAVITY;
        ///mesh
        vertices = new double[36];
        vertices[0] = ((double)width) + posx;
        vertices[1] = posy;
        vertices[2] = ((double)lenght) + posz;
        vertices[3] = posx;
        vertices[4] = posy;
        vertices[5] = ((double)lenght) + posz;
        vertices[6] = posx + ((double)width / 2.0);
        vertices[7] = ((double)height) + posy;
        vertices[8] = posz + ((double)lenght / 2.0);
        vertices[9] = posx;
        vertices[10] = posy;
        vertices[11] = posz;
        vertices[12] = posx;
        vertices[13] = posy;
        vertices[14] = posz;
        vertices[15] = posx + ((double)width / 2.0);
        vertices[16] = ((double)height) + posy;
        vertices[17] = posz + ((double)lenght / 2.0);
        vertices[18] = posx;
        vertices[19] = posy;
        vertices[20] = posz;
        vertices[21] = ((double)width) + posx;
        vertices[22] = posy;
        vertices[23] = posz;
        vertices[24] = posx + ((double)width / 2.0);
        vertices[25] = ((double)height) + posy;
        vertices[26] = posz + ((double)lenght / 2.0);
        vertices[27] = ((double)width) + posx;
        vertices[28] = posy;
        vertices[29] = posz;
        vertices[30] = ((double)width) + posx;
        vertices[31] = posy;
        vertices[32] = ((double)lenght) + posz;
        vertices[33] = posx + ((double)width / 2.0);
        vertices[34] = ((double)height) + posy;
        vertices[35] = posz + ((double)lenght / 2.0);

        ///normal
        normals = new double[36];
        up = Vector(0.0 , (double)height, -(double)lenght / 2.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normals[6] = normals[3] = normals[0] = temp.x;
        normals[7] = normals[4] = normals[1] = temp.y;
        normals[8] = normals[5] = normals[2] = temp.x;
        up = Vector((double)width / 2.0 , (double)height, 0.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normals[15] = normals[12] = normals[9] = temp.x;
        normals[16] = normals[13] = normals[10] = temp.y;
        normals[17] = normals[14] = normals[11] = temp.x;
        up = Vector(0.0 , (double)height, (double)lenght / 2.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normals[18] = normals[21] = normals[24] = temp.x;
        normals[19] = normals[22] = normals[25] = temp.y;
        normals[20] = normals[23] = normals[26] = temp.x;
        up = Vector(-(double)width / 2.0 , (double)height, 0.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normals[27] = normals[30] = normals[33] = temp.x;
        normals[28] = normals[31] = normals[34] = temp.y;
        normals[29] = normals[32] = normals[35] = temp.x;

        ///coordoné de texture
        texCoords = new double[24];
        texCoords[0] = 1.0;
        texCoords[1] = 1.0;
        texCoords[2] = 0.0;
        texCoords[3] = 1.0;
        texCoords[4] = 0.5;
        texCoords[5] = 0.0;


        texCoords[6] = 1.0;
        texCoords[7] = 1.0;
        texCoords[8] = 0.0;
        texCoords[9] = 1.0;
        texCoords[10] = 0.5;
        texCoords[11] = 0.0;

        texCoords[12] = 1.0;
        texCoords[13] = 1.0;
        texCoords[14] = 0.0;
        texCoords[15] = 1.0;
        texCoords[16] = 0.5;
        texCoords[17] = 0.0;

        texCoords[18] = 1.0;
        texCoords[19] = 1.0;
        texCoords[20] = 0.0;
        texCoords[21] = 1.0;
        texCoords[22] = 0.5;
        texCoords[23] = 0.0;




        //todo hitbox

        verticesHitBox = new double[36];
        verticesHitBox[0] = ((double)width) + posx;
        verticesHitBox[1] = posy;
        verticesHitBox[2] = ((double)lenght) + posz;
        verticesHitBox[3] = posx;
        verticesHitBox[4] = posy;
        verticesHitBox[5] = ((double)lenght) + posz;
        verticesHitBox[6] = posx + ((double)width / 2.0);
        verticesHitBox[7] = ((double)height) + posy;
        verticesHitBox[8] = posz + ((double)lenght / 2.0);
        verticesHitBox[9] = posx;
        verticesHitBox[10] = posy;
        verticesHitBox[11] = posz;
        verticesHitBox[12] = posx;
        verticesHitBox[13] = posy;
        verticesHitBox[14] = posz;
        verticesHitBox[15] = posx + ((double)width / 2.0);
        verticesHitBox[16] = ((double)height) + posy;
        verticesHitBox[17] = posz + ((double)lenght / 2.0);
        verticesHitBox[18] = posx;
        verticesHitBox[19] = posy;
        verticesHitBox[20] = posz;
        verticesHitBox[21] = ((double)width) + posx;
        verticesHitBox[22] = posy;
        verticesHitBox[23] = posz;
        verticesHitBox[24] = posx + ((double)width / 2.0);
        verticesHitBox[25] = ((double)height) + posy;
        verticesHitBox[26] = posz + ((double)lenght / 2.0);
        verticesHitBox[27] = ((double)width) + posx;
        verticesHitBox[28] = posy;
        verticesHitBox[29] = posz;
        verticesHitBox[30] = ((double)width) + posx;
        verticesHitBox[31] = posy;
        verticesHitBox[32] = ((double)lenght) + posz;
        verticesHitBox[33] = posx + ((double)width / 2.0);
        verticesHitBox[34] = ((double)height) + posy;
        verticesHitBox[35] = posz + ((double)lenght / 2.0);


        normalsHitBox = new double[36];
        up = Vector(0.0 , (double)height, -(double)lenght / 2.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normalsHitBox[6] = normalsHitBox[3] = normalsHitBox[0] = temp.x;
        normalsHitBox[7] = normalsHitBox[4] = normalsHitBox[1] = temp.y;
        normalsHitBox[8] = normalsHitBox[5] = normalsHitBox[2] = temp.x;
        up = Vector((double)width / 2.0 , (double)height, 0.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normalsHitBox[15] = normalsHitBox[12] = normalsHitBox[9] = temp.x;
        normalsHitBox[16] = normalsHitBox[13] = normalsHitBox[10] = temp.y;
        normalsHitBox[17] = normalsHitBox[14] = normalsHitBox[11] = temp.x;
        up = Vector(0.0 , (double)height, (double)lenght / 2.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normalsHitBox[18] = normalsHitBox[21] = normalsHitBox[24] = temp.x;
        normalsHitBox[19] = normalsHitBox[22] = normalsHitBox[25] = temp.y;
        normalsHitBox[20] = normalsHitBox[23] = normalsHitBox[26] = temp.x;
        up = Vector(-(double)width / 2.0 , (double)height, 0.0);
        temp = (Vector(vertices[0] - vertices[3], 0.0, vertices[2] - vertices[5]) % up);
        normalsHitBox[27] = normalsHitBox[30] = normalsHitBox[33] = temp.x;
        normalsHitBox[28] = normalsHitBox[31] = normalsHitBox[34] = temp.y;
        normalsHitBox[29] = normalsHitBox[32] = normalsHitBox[35] = temp.x;
    }

    double getRealWeight(){
        return realWeight;
    }

};

#endif