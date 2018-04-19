/// \brief L'ombrage est qu'est-ce que chaque modèle a. Elle est d'une couleur noire semi-transparente.
/// \details Un ombrage est une projection 3D sur une plane 2D infinie (ax + by + cz = 0; y=0). Cette projection utilise les connaissances acquises en algèbre linéaire et la géométrie vectorielle.
/// \author Tai Chen Li
/// \date 19 avril 2018
/// \version 0.1
/// \warning L'ombrage se situe seulement à la hauteur y=0. Donc, s'il y a quelque chose qui bloque la vision sur le sol à y=0, on ne verra rien.
/// \bug Aucuns.

#ifndef SHADING_H
#define SHADING_H

#include "includes.h"

class Shading : public Model {
private:
    double *colors;

    void updateNormalColor() {
        for (int i = 0; i < coordsCount; ++i) {
            normals[i] = 0.0;
            normals[i * 3 + 1] = 1.0;
            normals[i * 3 + 2] = 0.0;
            colors[i * 4] = 0; // red
            colors[i * 4 + 1] = 0; // green
            colors[i * 4 + 2] = 0; // blue
            colors[i * 4 + 3] = 127; // alpha
        }
    }

public:
    Shading(Model* obstruction, Vector sun) : Model(NULL, NULL, NULL, NULL, NULL, nullptr) {
        colors = nullptr;
        this-> vertexCount = obstruction->vertexCount;
        this-> normalCount = obstruction->normalCount;
        colors = new double[vertexCount * 4];
        updateNormalColor();
        updateShadingVertex(obstruction, sun);
    }

    ~Shading() {
        delete[] colors;
    }

    void updateShadingVertex(Model* obstruction, Vector sun) {
        Vector AB, B;
        double k = 0.0;
        unsigned int coordsCount = obstruction->vertexCount / 3;

        for (int i = 0; i < coordsCount; ++i) {
            B = Vector(obstruction->vertices[i * 3], obstruction->vertices[i * 3 + 1], obstruction->vertices[i * 3 + 2]);
            AB = B - sun; // OB - OA = AB
            k = -(B.y)/(AB.y); // la quantité à multiplier à chacune des composantes pour atteindre notre plan y = 0
            vertices[i] = k * AB.x + B.x;
            vertices[i * 3 + 1] = 0.0;
            vertices[i * 3 + 2] = k * AB.z + B.z;
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