/// \brief La maille est la somme de tous les points pour former une forme géométrique dans OpenGL.
/// \details
/// \author Tai Chen Li, samuel Labelle, Gabriel Bourdages
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.


#ifndef SOURCE_MODEL_H
#define SOURCE_MODEL_H

#include "Observer.h"

class Model : public Resource, public Observer<SDL_Event*> {
protected:
    unsigned int vertexCount; ///< Nombre de vertice
    unsigned int texCount; ///< Nombre de coordonné de texture
    unsigned int normalCount; ///< Nombre de normal
    double *vertices, *texCoords, *normals;

    unsigned int x; ///< Position du model en x
    unsigned int y; ///< Position du model en y
    unsigned int z; ///< Position du model en z

    unsigned int width; ///< Largeur du model (pour image en 2D)
    unsigned int height; ///< Hauteur du model (pour image en 2D)

    unsigned int textureID; ///< Identificateur de la texture

public:

	/// Constructeur.
    /// \param textureID Identificateur de la texture.
	/// \param objFile Nom du fichier depuis lequel charger le modèle, au format Wavefront (.obj).
    Model(unsigned int textureID, const char* objFile = nullptr) {
        this->textureID = textureID;

        vertexCount = texCount = normalCount = 0;
        vertices = normals = texCoords = nullptr;

        if(objFile) {
            std::vector<double> vVertices, vNormals, vTexCoords;
            std::vector<unsigned int> vVerticesIndex, vNormalsIndex, vTexCoordsIndex;

            //vVertices.push_back(0.0);

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
        }
            /* ANCIEN CHARGEUR DE MODEL

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
        } */
    }


	/// Destructeur.
    ~Model() {
        delete[] vertices;
        delete[] normals;
        delete[] texCoords;
    }

	/// Applique une matrice de transformation au modèle.
	/// \param m Matrice de transformation.
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

	/// Affiche le modèle.
    void draw() {
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
