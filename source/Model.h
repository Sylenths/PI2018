/// \brief La maille est la somme de tous les points pour former une forme géométrique dans OpenGL.
/// \details
/// \author Tai Chen Li, Samuel Labelle, Gabriel Bourdages, Mathilde Harnois
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Bug graphique avec l'ombre

#ifndef SOURCE_MODEL_H
#define SOURCE_MODEL_H

#include "Matrix.h"

class Model : public Entity, public Observer<SDL_Event*> {
	friend class Physics;

protected:
    unsigned int vertexCount; ///< Nombre de vertice
    unsigned int texCount; ///< Nombre de coordonné de texture
    unsigned int normalCount; ///< Nombre de normal
    double *vertices, *texCoords, *normals, *verticesHitBox, *normalsHitBox;

    double *verticesShading; ///< Nombre de vertices pour l'ombrage
    double *normalsShading; ///< Nombre de normales pour l'ombrage
    double *colorsShading; ///< Un tableau de couleur RGBA pour chacun des triangles

    unsigned int textureToDraw; ///< Identificateur de la texture

    double posx, posy, posz;
    bool rotHitBox;

    bool shading;

    Vector baseCenter;
    Vector realCenter;

    std::map<std::string, unsigned int> textureIDs;

    /// Crée l'ombre du modèle
    /// \param sun Vecteur indiquant la position du soleil
    void updateShadingVertex(Vector sun) {
        Vector AB, B;
        double k;

        Vector temp;

        for (int i = 0; i < vertexCount; ++i) {
            B = Vector(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
            AB = B - sun; // OB - OA = AB

            k = ((0.1 - B.y)/(AB.y)); // la quantité à multiplier à chacune des composantes pour atteindre notre plan y = 0
            verticesShading[i * 3    ] = k*AB.x + B.x;
            verticesShading[i * 3 + 1] = 0.1;
            verticesShading[i * 3 + 2] = k*AB.z + B.z;
        }
    }

    bool signOfD(double& xCordp, double& zCordp, double& xCord1, double& zCord1, double& xCord2, double& zCord2) {
        if (((xCordp - xCord1) * (zCord2 - zCord1) - (zCordp - zCord1) * (xCord2 - xCord1)) < 0)
            return false;
        else
            return true;
    }

    /// Enlève les triangles de surplus dans l'ombre afin d'enlever les superpositions
    void cleanShadingVertex() {
        bool signRef;
        double* shadingEdges;
        std::vector<double> vShadingEdges;

        for (int i = 0; i < (vertexCount / 3); i += 9) {
            signRef = signOfD(verticesShading[i + 6], verticesShading[i + 8], verticesShading[i], verticesShading[i + 2], verticesShading[i + 3], verticesShading[i + 5]);
            for (int j = 0; j < (vertexCount - 2); j += 3) {
                //Si le point j ne fait pas parti du segment
                if (!(j == i || j == (i + 3))) {
                    //Si le déterminant est du même signe que le signe de référence du triangle
                    if (signOfD(verticesShading[j], verticesShading[j + 2], verticesShading[i], verticesShading[i + 2], verticesShading[i + 3], verticesShading[i + 5]) == signRef) {
                        //Si c'est le dernier sommet
                        if (j == (vertexCount - 3)) {
                            for (int k = 0; k < 6; k++) {
                                //on ajoute le segment (6 sommets) au tableau de sommets qui composent les extrémités de l'ombre
                                vShadingEdges.push_back(verticesShading[j + k]);
                            }
                        }
                    } else {
                        //on arrête la boucle et on va au prochain segment
                        j = vertexCount;
                    }
                }
            }

            for (int j = 0; j < (vertexCount - 2); j += 3) {
                if (!(j == (i + 3) || j == (i + 6))) {
                    if (signOfD(verticesShading[j], verticesShading[j + 2], verticesShading[i + 3], verticesShading[i + 5], verticesShading[i + 6], verticesShading[i + 8]) == signRef) {
                        if (j == (vertexCount - 3)) {
                            for (int k = 0; k < 6; k++) {
                                vShadingEdges.push_back(verticesShading[j + k]);
                            }
                        }
                    }
                    else
                        j = vertexCount;
                }
            }

            for (int j = 0; j < (vertexCount - 2); j += 3) {
                if (!(j == (i + 3) || j == (i + 6))) {
                    if (signOfD(verticesShading[j], verticesShading[j + 2], verticesShading[i + 6], verticesShading[i + 8], verticesShading[i], verticesShading[i + 2]) == signRef) {
                        if (j == (vertexCount - 3)) {
                            for (int k = 0; k < 6; k++) {
                                vShadingEdges.push_back(verticesShading[j + k]);
                            }
                        }
                    }
                    else {
                        j = vertexCount;
                    }
                }
            }
        }
    }

public:
    std::function<void()> onClick;  ///< Pointeur de méthode réagissant à un click de souris.

    /// Applique une matrice de transformation au modèle.
    /// \param m Matrice de transformation.
    void transform(Matrix& m){//matrix not being a reference causes crashes (because no copy constructor is defined)
        unsigned int x, y, z;
        baseCenter = m * baseCenter;
        realCenter = m * realCenter;
        for (int i = 0; i < vertexCount; ++i) {
        x = i * 3;
        y = x + 1;
        z = x + 2;


        Vector nv = m * Vector(vertices[x], vertices[y], vertices[z]);
        vertices[x] = nv.x;
        vertices[y] = nv.y;
        vertices[z] = nv.z;

          



            nv = m * Vector(normals[x], normals[y], normals[z]);
        normals[x] = nv.x;
        normals[y] = nv.y;
        normals[z] = nv.z;
        }

        if(vertexCount) {
            for (int i = 0; i < 36; ++i) {
            x = i * 3;
            y = x + 1;
            z = x + 2;

            if(rotHitBox) {
                Vector nv = m * Vector(verticesHitBox[x] - m.m14, verticesHitBox[y] - m.m24, verticesHitBox[z] - m.m34);
                verticesHitBox[x] = nv.x;
                verticesHitBox[y] = nv.y;
                verticesHitBox[z] = nv.z;

                nv = m * Vector(normalsHitBox[x] - m.m14, normalsHitBox[y] - m.m24, normalsHitBox[z] - m.m34);
                normalsHitBox[x] = nv.x;
                normalsHitBox[y] = nv.y;
                normalsHitBox[z] = nv.z;
            }
            verticesHitBox[x] += m.m14;
            verticesHitBox[y] += m.m24;
            verticesHitBox[z] += m.m34;

            normalsHitBox[x] += m.m14;
            normalsHitBox[y] += m.m24;
            normalsHitBox[z] += m.m34;
            }
        }

    }

    /// Constructeur.
    /// \param textureID Identificateur de la texture.
	/// \param objFile Nom du fichier depuis lequel charger le modèle, au format Wavefront (.obj).
    Model(const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Entity(name) {
        this->posx = posx;
        this->posy = posy;
        this->posz = posz;
        this->rotHitBox = rotHitBox;
        double ymax;


        shading = false;

        colorsShading = nullptr;

        textureIDs["default"] = textureID;
        textureToDraw = textureID;

        vertexCount = texCount = normalCount = 0;
        vertices = normals = texCoords = nullptr;

        if(objFile) {
            std::vector<double> vVertices, vNormals, vTexCoords;
            std::vector<unsigned int> vVerticesIndex, vNormalsIndex, vTexCoordsIndex;

            std::string str = " ";
            std::ifstream fichier(objFile);
            while(!str.empty()) {
                str.clear();
                fichier >> str;
                double composante;
                unsigned int index;
                switch(str[0]) {
                    case 'v' :
                        if(str.size() == 1) {
                            // TODO: Lire composante du sommet...
                            for(int i = 0; i < 3; i++) {
                                fichier >> composante;
                                vVertices.push_back(composante);
                            }
                        }
                        else
                            switch(str[1]) {
                                case 't':
                                    // TODO: Lire coordo texture...
                                    for(int i = 0; i < 2; i++) {
                                        fichier >> composante;
                                        vTexCoords.push_back(composante);
                                    }
                                    break;

                                case 'n':
                                    //TODO: Lire composante normales...
                                    for(int i = 0; i < 3; i++) {
                                        fichier >> composante;
                                        vNormals.push_back(composante);
                                    }
                                    break;
                            }
                        break;
                    case 'f' :
                        for(int i = 0; i < 3; i++) {
                            fichier >> index;
                            vVerticesIndex.push_back(index);
                            fichier.ignore();

                            fichier >> index;
                            vTexCoordsIndex.push_back(index);
                            fichier.ignore();

                            fichier >> index;
                            vNormalsIndex.push_back(index);
                            fichier.ignore();
                        }
                        break;

                    default:
                        fichier.ignore(30, 10);
                        break;
                }
            }
            // TODO: lire...
            vertexCount = vVerticesIndex.size();
            unsigned int xi, yi, zi, x, y, z;

            vertices = new double[3 * vertexCount];
            for(int i = 0; i < vertexCount; i++) {
                xi = ((vVerticesIndex[i] - 1) * 3);
                yi = xi + 1;
                zi = xi + 2;
                x = i * 3;
                y = x + 1;
                z = x + 2;
                vertices[x] = vVertices[xi];
                vertices[y] = vVertices[yi];
                vertices[z] = vVertices[zi];
            }

            texCoords = new double[2 * vertexCount];
            for(int i = 0; i < vertexCount; i++) {
                xi = ((vTexCoordsIndex[i] - 1) * 2);
                yi = xi + 1;
                x = i * 2;
                y = x + 1;
                texCoords[x] = vTexCoords[xi];
                texCoords[y] = 1 - vTexCoords[yi];
            }

            normals = new double[3 * vertexCount];
            for(int i = 0; i < vertexCount; i++) {
                xi = ((vNormalsIndex[i] - 1) * 3);
                yi = xi + 1;
                zi = xi + 2;
                x = i * 3;
                y = x + 1;
                z = x + 2;
                normals[x] = vNormals[xi];
                normals[y] = vNormals[yi];
                normals[z] = vNormals[zi];
            }

            fichier.close();
            double xmin = 0.0, xmax = 0.0, ymin = 0.0, zmin = 0.0, zmax = 0.0;
            ymax = 0.0;
            for(int i = 0; i < vertexCount; i++) {
                int x, y, z;
                 x = i * 3;
                 y = x + 1;
                 z = x + 2;
                 if(vertices[x] < xmin)
                     xmin = vertices[x];
                 if(vertices[x] > xmax)
                     xmax = vertices[x];
                 if(vertices[y] < ymin)
                     ymin = vertices[y];
                 if(vertices[y] > ymax)
                     ymax = vertices[y];
                 if(vertices[z] < zmin)
                     zmin = vertices[z];
                 if(vertices[z] > zmax)
                     zmax = vertices[z];
            }
                 verticesHitBox = new double[108] {
                         xmax, ymax, zmax, //P1T1F1
                         xmax, ymin, zmax, //P2T1F1
                         xmin, ymin, zmax, //P3T1F1

                         xmax, ymax, zmax, //P1T2F1
                         xmin, ymax, zmax, //P2T2F1
                         xmin, ymin, zmax, //P3T2F1

                         xmax, ymax, zmin, //P1T1F2
                         xmax, ymin, zmin, //P2T1F2
                         xmin, ymin, zmin, //P3T1F2

                         xmax, ymax, zmin, //P1T2F2
                         xmin, ymax, zmin, //P2T2F2
                         xmin, ymin, zmin, //P3T2F2

                         xmax, ymax, zmax, //P1T1F3
                         xmax, ymax, zmin, //P2T1F3
                         xmax, ymin, zmax, //P3T1F3

                         xmax, ymin, zmax, //P1T2F3
                         xmax, ymin, zmin, //P2T2F3
                         xmax, ymax, zmin, //P3T2F3

                         xmin, ymax, zmax, //P1T1F4
                         xmin, ymax, zmin, //P2T1F4
                         xmin, ymin, zmax, //P3T1F4

                         xmin, ymin, zmax, //P1T2F4
                         xmin, ymin, zmin, //P2T2F4
                         xmin, ymax, zmin, //P3T2F4

                         xmax, ymax, zmax, //P1T1F5
                         xmin, ymax, zmax, //P2T1F5
                         xmax, ymax, zmin, //P3T1F5

                         xmin, ymax, zmax, //P1T2F5
                         xmin, ymax, zmin, //P2T2F5
                         xmax, ymax, zmin, //P3T2F5

                         xmax, ymin, zmax, //P1T1F6
                         xmin, ymin, zmax, //P2T1F6
                         xmax, ymin, zmin, //P3T1F6

                         xmin, ymin, zmax, //P1T2F6
                         xmin, ymin, zmin, //P2T2F6
                         xmax, ymin, zmin, //P3T2F6
                 };

                 normalsHitBox = new double[108] {
                         0.0, 0.0, 1.0, //P1T1F1
                         0.0, 0.0, 1.0, //P2T1F1
                         0.0, 0.0, 1.0, //P3T1F1

                         0.0, 0.0, 1.0, //P1T2F1
                         0.0, 0.0, 1.0, //P2T2F1
                         0.0, 0.0, 1.0, //P3T2F1

                         0.0, 0.0, -1.0, //P1T1F2
                         0.0, 0.0, -1.0, //P2T1F2
                         0.0, 0.0, -1.0, //P3T1F2

                         0.0, 0.0, -1.0, //P1T2F2
                         0.0, 0.0, -1.0, //P2T2F2
                         0.0, 0.0, -1.0, //P3T2F2

                         1.0, 0.0, 0.0, //P1T1F3
                         1.0, 0.0, 0.0, //P2T1F3
                         1.0, 0.0, 0.0, //P3T1F3

                         1.0, 0.0, 0.0, //P1T2F3
                         1.0, 0.0, 0.0, //P2T2F3
                         1.0, 0.0, 0.0, //P3T2F3

                         -1.0, 0.0, 0.0, //P1T1F4
                         -1.0, 0.0, 0.0, //P2T1F4
                         -1.0, 0.0, 0.0, //P3T1F4

                         -1.0, 0.0, 0.0, //P1T2F4
                         -1.0, 0.0, 0.0, //P2T2F4
                         -1.0, 0.0, 0.0, //P3T2F4

                         0.0, 1.0, 0.0, //P1T1F5
                         0.0, 1.0, 0.0, //P2T1F5
                         0.0, 1.0, 0.0, //P3T1F5

                         0.0, 1.0, 0.0, //P1T2F5
                         0.0, 1.0, 0.0, //P2T2F5
                         0.0, 1.0, 0.0, //P3T2F5

                         0.0, -1.0, 0.0, //P1T1F6
                         0.0, -1.0, 0.0, //P2T1F6
                         0.0, -1.0, 0.0, //P3T1F6

                         0.0, -1.0, 0.0, //P1T2F6
                         0.0, -1.0, 0.0, //P2T2F6
                         0.0, -1.0, 0.0, //P3T2F6
                 };


       }
       baseCenter = Vector(0.0, 0.0, 0.0);
       realCenter = Vector(0.0, ymax/2, 0.0);
       Matrix m;
       m.loadTranslation(Vector(posx, posy, posz));
       transform(m);
    }

    void setShadingOn() {
        shading = true;
    }
    ///Constructeur de mur
    Model(const std::string& name, unsigned int height, unsigned int textureID, Vector* firstCorner, Vector* secondCorner) : Entity(name) {


        textureIDs["default"] = textureID;
        textureToDraw = textureID;
        vertices = normals = texCoords = nullptr;
        Vector up = {0.0, 1.0, 0.0};
        Vector temp;
        vertexCount = 6;
        normalCount = 6;
        texCount = 6;

        shading = false;

        colorsShading = nullptr;

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
   }

    ///Constructeur de toit
    Model(const std::string& name, unsigned int width, unsigned int height, unsigned int lenght, double posx, double posy, double posz, unsigned int textureID) : Entity(name) {
        textureIDs["default"] = textureID;
        textureToDraw = textureID;
        normalsHitBox, verticesHitBox, vertices = normals = texCoords = nullptr;
        Vector up;
        Vector temp;
        vertexCount = 12;
        normalCount = 12;
        texCount = 12;

        rotHitBox = false;

        shading = false;
        colorsShading = nullptr;

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


    /// Destructeur.
    ~Model() {
        delete[] vertices;
        delete[] normals;
        delete[] texCoords;

        if (colorsShading != nullptr) {
            delete[] verticesShading;
            delete[] normalsShading;
            delete[] colorsShading;
        }
    }

    void setTexture(std::string name = "", unsigned int ID = 0) {
        if ((name == "") && (ID == 0))
            textureToDraw = textureIDs["default"];
        else
            if ((name != "") && (ID != 0))
                    textureIDs[name] = textureToDraw = ID;
    }


	/// Affiche le modèle.
    virtual void draw() {
        glBindTexture(GL_TEXTURE_2D, textureToDraw);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    void drawAndShading(Vector lightPos) {
            draw();

            if (shading == true) {

                if (colorsShading == nullptr) {
                    verticesShading = new double[vertexCount * 3];
                    normalsShading = new double[vertexCount * 3];
                    colorsShading = new double[vertexCount * 4];

                    for (int i = 0; i < vertexCount; ++i) {
                        normalsShading[i] = 0.0;
                        normalsShading[i * 3 + 1] = 1.0;
                        normalsShading[i * 3 + 2] = 0.0;
                        colorsShading[i * 4    ] = 0; // red
                        colorsShading[i * 4 + 1] = 0; // green
                        colorsShading[i * 4 + 2] = 0; // blue
                        colorsShading[i * 4 + 3] = 127; // alpha
                    }
                }

                updateShadingVertex(lightPos);

                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_NORMAL_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                glVertexPointer(3, GL_DOUBLE, 0, verticesShading);
                glNormalPointer(GL_DOUBLE, 0, normalsShading);
                glColorPointer(4, GL_DOUBLE, 0, colorsShading);

                glDrawArrays(GL_TRIANGLES, 0, vertexCount);

                glDisableClientState(GL_VERTEX_ARRAY);
                glDisableClientState(GL_NORMAL_ARRAY);
                glDisableClientState(GL_COLOR_ARRAY);
            }
    }

    double getMesh(int position){
        return (vertices[position]);
    }

    virtual void notify(SDL_Event* sdlEvent) {}

    const std::string getType() {
        return "Model";
    }
};

#endif
