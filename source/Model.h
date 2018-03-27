/// \brief La maille est la somme de tous les points pour former une forme géométrique dans OpenGL.
/// \details
/// \author Tai Chen Li
/// \date 25 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef SOURCE_MODEL_H
#define SOURCE_MODEL_H

#include "Resource.h"
#include "Observer.h"
#include "TextureID.h"
#include "Mesh.h"
#include "ResourceManager.h"

class Model : public Resource, public Observer<SDL_Event*> {
protected:
    unsigned int vertexCount;
    unsigned int texCount;
    unsigned int normalCount;
    double *vertices, *texCoords, *normals;

    unsigned int textureID;

public:
    Model(std::string textureName, const char* objFile = nullptr) {
        textureID = ResourceManager::getInstance()->getTexture(textureName);

        vertexCount = texCount = normalCount = 0;
        vertices = normals = texCoords = nullptr;

        if(objFile) {
            std::vector<double> vVertices, vTexCoords, vNormals;
            std::vector<double> verticesEasy, texEasy, normalsEasy;

            double tempDouble = 0.0;
            //char tempChar;

            unsigned int tempInt = 0;

            std::string str = " ";
            std::ifstream fichier(objFile);
            while (!str.empty()) {
                str.clear();
                fichier >> str;

                switch(str[0]) {
                    case 'v':
                        if (str.size() == 1) {
                            for (int i = 0; i < 3; ++i) {
                                fichier >> tempDouble; // s'arrête quand ce n'est plus un double
                                vVertices.push_back(tempDouble);
                            }
                        }
                        else {
                            switch (str[1]) {
                                case 't':
                                    // TODO: Lire coordonnée de la texture.
                                    for (int i = 0; i < 2; ++i) {
                                        fichier >> tempDouble;
                                        vTexCoords.push_back(tempDouble);
                                    }
                                    break;
                                case 'n':
                                    // TODO: Lire composantes de la normale
                                    for (int i = 0; i < 3; ++i) {
                                        fichier >> tempDouble;
                                        vNormals.push_back(tempDouble);
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;
                    case 'f':
                        // unsigned int vVerticesNb = 0, vTexCoordsNb = 0, vNormalsNb = 0;

                        for (int i = 0; i < 3; ++i) {
                            fichier >> tempInt;
                            verticesEasy.push_back(vVertices[(tempInt - 1) * 3]);
                            verticesEasy.push_back(vVertices[(tempInt - 1) * 3 + 1]);
                            verticesEasy.push_back(vVertices[(tempInt - 1) * 3 + 2]);

                            //fichier >> tempChar;
                            fichier.ignore();
                            fichier >> tempInt;

                            texEasy.push_back(vTexCoords[(tempInt - 1) * 2]);
                            texEasy.push_back(vTexCoords[(tempInt - 1) * 2 + 1]);

                            //fichier >> tempChar;
                            fichier.ignore();
                            fichier >> tempInt;

                            normalsEasy.push_back(vNormals[(tempInt - 1) * 3]);
                            normalsEasy.push_back(vNormals[(tempInt - 1) * 3 + 1]);
                            normalsEasy.push_back(vNormals[(tempInt - 1) * 3 + 2]);
                        }

                        break;
                    default:
                        fichier.ignore(30, 10); // 10 est le saut de ligne
                        break;
                }
            }
            vertexCount = verticesEasy.size();
            texCount = texEasy.size();
            normalCount = normalsEasy.size();

            vertices = new double[vertexCount];
            texCoords = new double[texCount];
            normals = new double[normalCount];

            for (int i = 0; i < vertexCount; ++i) {
                vertices[i] = verticesEasy[i];
            }

            for (int i = 0; i < texCount; ++i) {
                texCoords[i] = texEasy[i];
            }

            for (int i = 0; i < normalCount; ++i) {
                normals[i] = normalsEasy[i];
            }

            // TODO: Lire...
            fichier.close();
        }
    }


    ~Model() {
        delete[] vertices;
        delete[] normals;
        delete[] texCoords;
    }

    void transform(Matrix m) {
        Vector3D nv;
        unsigned int x, y, z;

        for(int i = 0; i < vertexCount; ++i) {
            x = i * 3;
            y = x + 1;
            z = x + 2;

            nv = m * Vector3D(vertices[x] - m.m41, vertices[y] - m.m42, vertices[z] - m.m43);
            vertices[x] = nv.x + m.m41;
            vertices[y] = nv.y + m.m42;
            vertices[z] = nv.z + m.m43;

            nv = m * Vector3D(normals[x] - m.m41, normals[y] - m.m42, normals[z] - m.m43);
            normals[x] = nv.x + m.m41;
            normals[y] = nv.y + m.m42;
            normals[z] = nv.z + m.m43;

        }
    }


    virtual void draw() {
        glBindTexture(GL_TEXTURE_2D, textureID);

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
};


#endif //SOURCE_MODEL_H
