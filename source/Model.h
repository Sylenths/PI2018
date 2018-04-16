/// \brief La maille est la somme de tous les points pour former une forme géométrique dans OpenGL.
/// \details
/// \author Tai Chen Li, Samuel Labelle, Gabriel Bourdages
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_MODEL_H
#define SOURCE_MODEL_H
#include "Matrix.h"

class Model : public Resource, public Observer<SDL_Event*> {
protected:
    unsigned int vertexCount; ///< Nombre de vertice
    unsigned int texCount; ///< Nombre de coordonné de texture
    unsigned int normalCount; ///< Nombre de normal
    double *vertices, *texCoords, *normals, *verticesHitBox, *normalsHitBox;

    unsigned int textureToDraw; ///< Identificateur de la texture

    double posx, posy, posz;
    bool rotHitBox;

    std::map<std::string, unsigned int> textureIDs;

public:
    std::function<void()> onClick;  ///< Pointeur de méthode réagissant à un click de souris.

    /// Applique une matrice de transformation au modèle.
    /// \param m Matrice de transformation.
    void transform(Matrix& m){//matrix not being a reference causes crashes (because no copy constructor is defined)
        unsigned int x, y, z;
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
    Model(double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) {
        this->posx = posx;
        this->posy = posy;
        this->posz = posz;
        this->rotHitBox = rotHitBox;

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
            double xmin = 0.0, xmax = 0.0, ymin = 0.0, ymax = 0.0, zmin = 0.0, zmax = 0.0;
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
       Matrix m;
       m.loadTranslation(Vector(posx, posy, posz));
       transform(m);
    }

	/// Destructeur.
    ~Model() {
        delete[] vertices;
        delete[] normals;
        delete[] texCoords;
    }

    void setTexture(std::string name = "", unsigned int ID = 0) {
        if ((name == "") && (ID == 0))
            textureToDraw = textureIDs["default"];
        else
            if (name != "")
                if (ID)
                    textureToDraw = textureIDs[name];
                else
                    textureIDs[name] = textureToDraw = ID;
    }

	/// Affiche le modèle.
    void draw() {
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

    virtual void notify(SDL_Event* sdlEvent) {}
};

#endif //SOURCE_MODEL_H
