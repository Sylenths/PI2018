/// \brief La maille est la somme de tous les points pour former une forme géométrique dans OpenGL.
/// \details
/// \author Tai Chen Li, Samuel Labelle, Gabriel Bourdages
/// \date 28 mars 2018
/// \version 0.2
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_MODEL_H
#define SOURCE_MODEL_H

class Model : public Resource, public Observer<SDL_Event*> {
protected:
    unsigned int vertexCount; ///< Nombre de vertice
    unsigned int texCount; ///< Nombre de coordonné de texture
    unsigned int normalCount; ///< Nombre de normal
    double *vertices, *texCoords, *normals;

    unsigned int textureToDraw; ///< Identificateur de la texture

    std::map<std::string, unsigned int> textureIDs;

public:
	/// Constructeur.
    /// \param textureID Identificateur de la texture.
	/// \param objFile Nom du fichier depuis lequel charger le modèle, au format Wavefront (.obj).
    Model(unsigned int textureID, const char* objFile = nullptr) {
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
        }
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
