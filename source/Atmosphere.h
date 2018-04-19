/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et sa couleur
/// \author Mathilde Harnois
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#include "includes.h"

class Atmosphere : public Model {
private:
    double *colors;

public:

    Atmosphere(double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Model(posx, posy, posz, textureID, rotHitBox, objFile) {
        colors = nullptr;

        if(objFile) {
            colors = new double[4 * vertexCount];
            for(int i = 0; i < vertexCount; i+= 4) {
                colors[i] = 0;
                colors[i + 1] = 0;
                colors[i + 2] = 255;
                colors[i + 3] = 0;
            }
        }
    }

    ~Atmosphere() {
        delete[] colors;
    }

    void lighten (Chrono deltaTime) {
        for(int i = 3; i < vertexCount; i+= 4) {
            colors[i] -= 2.83 * pow(10, -6);
        }
    }

    void darken (Chrono deltaTime) {
        for(int i = 3; i < vertexCount; i+= 4) {
            colors[i] += 2.83 * pow(10, -6);
        }
    }

    void changeToRed() {
        for(int i = 0; i < vertexCount; i+= 4) {
            colors[i] = 255;
            colors[i + 1] = 0;
            colors[i + 2] = 0;
        }
    }

    void changeToGreen() {
        for(int i = 0; i < vertexCount; i+= 4) {
            colors[i] = 0;
            colors[i + 1] = 255;
            colors[i + 2] = 0;
        }
    }

    void changeToBlue() {
        for(int i = 0; i < vertexCount; i+= 4) {
            colors[i] = 0;
            colors[i + 1] = 255;
            colors[i + 2] = 0;
        }
    }

    void changeToWhite() {
        for(int i = 0; i < vertexCount; i+= 4) {
            colors[i] = 255;
            colors[i + 1] = 255;
            colors[i + 2] = 255;
        }
    }

    void changeToBlack() {
        for(int i = 0; i < vertexCount; i+= 4) {
            colors[i] = 0;
            colors[i + 1] = 0;
            colors[i + 2] = 0;
        }
    }

    void draw() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glColorPointer(4, GL_DOUBLE, 0, colors);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }

};


#endif
