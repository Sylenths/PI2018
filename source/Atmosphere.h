/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et sa couleur
/// \author Mathilde Harnois, Guillaume Julien-Desmarchais
/// \date 17 avril 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns.

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#include "includes.h"

class Atmosphere : public Model {
private:
    unsigned int atmosphereTextureId;

    bool dayTime;

    Uint32 *pixel;

public:

    Atmosphere(double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Model(posx, posy, posz, textureID, rotHitBox, objFile) {
        pixel = new Uint32;

        pixel[0] = 200;//A
        pixel[0] = (pixel[0] << 8) | 38;//B
        pixel[0] = (pixel[0] << 8) | 145;//G
        pixel[0] = (pixel[0] << 8) | 211;//R

        glGenTextures(1, &atmosphereTextureId);
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    ~Atmosphere() {
        delete pixel;
    }

    void lighten(Chrono deltaTime){
        pixel[0] -= (0.0 * deltaTime.getElapsed(MILISECONDS));//Alpha 0.00044444
        pixel[0] = (pixel[0] << 8) | 38;//B
        pixel[0] = (pixel[0] << 8) | 145;//G
        pixel[0] = (pixel[0] << 8) | 211;//R
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
}

    void darken(Chrono deltaTime){
        int opacity = 0.000444 * deltaTime.getElapsed(MILISECONDS);
        pixel[0] = opacity;
        pixel[0] = (pixel[0] << 8) | 255;//B
        pixel[0] = (pixel[0] << 8) | 255;//G
        pixel[0] = (pixel[0] << 8) | 255;//R
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    }



    void adjustColor(){
        if (dayTime){


        }
    }

    void draw() {
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);

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
#endif
