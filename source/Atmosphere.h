/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et sa couleur
/// \author Mathilde Harnois, Guillaume Julien-Desmarchais
/// \date 17 avril 2018
/// \version 0.5
/// \warning Le chrono de projet final doit restart a chaque debut de journée et de nuit
/// \bug

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#define HALFTURN 450 //seconds

#include "includes.h"

class Atmosphere : public Model {
private:
    unsigned int atmosphereTextureId, alpha;
    Chrono* atmoChrono;
    bool dayTime;
    Uint32 *pixel;

public:

    Atmosphere(double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : Model(posx, posy, posz, textureID, rotHitBox, objFile) {
        pixel = new Uint32;
        dayTime = true;
        alpha = 220;
        atmoChrono = new Chrono();
        pixel[0] = alpha;//A
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
        delete atmoChrono;
    }

    void lightenDay() {
        if(alpha - 1 >= 0) {
            pixel[0] = --alpha;
            pixel[0] = (pixel[0] << 8) | 38;//B
            pixel[0] = (pixel[0] << 8) | 145;//G
            pixel[0] = (pixel[0] << 8) | 211;//R
            glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        }
    }

    void darkenDay() {
        if (alpha + 1 <= 255) {
            pixel[0] = ++alpha;
            pixel[0] = (pixel[0] << 8) | 40;//B
            pixel[0] = (pixel[0] << 8) | 0;//G
            pixel[0] = (pixel[0] << 8) | 0;//R
            glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        }
    }


     void lightenNight() {
        if(alpha - 1 >= 0) {
            pixel[0] = --alpha;
            pixel[0] = (pixel[0] << 8) | 38;//B
            pixel[0] = (pixel[0] << 8) | 145;//G
            pixel[0] = (pixel[0] << 8) | 211;//R
            glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        }
    }

    void darkenNight() {
        if (alpha + 1 <= 255) {
            pixel[0] = ++alpha;
            pixel[0] = (pixel[0] << 8) | 40;//B
            pixel[0] = (pixel[0] << 8) | 0;//G
            pixel[0] = (pixel[0] << 8) | 0;//R
            glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        }
    }


    void updateAtmosphere(Chrono time) {
        if (atmoChrono->getElapsed(SECONDS) >= 2.5) { //A chaque 2.5 secondes
            atmoChrono->restart();
            if (dayTime) {
                if (time.getElapsed(SECONDS) > HALFTURN) //Si Passer milieu journee
                    darkenDay();
                else
                    lightenDay();
            }

            else
            if (time.getElapsed(SECONDS) > HALFTURN)//Si passer milieu nuit
                lightenNight();
            else
                darkenNight();
        }
    }


    void setNightColor(){
        pixel[0] = alpha;//A
        pixel[0] = (pixel[0] << 8) | 40;//B
        pixel[0] = (pixel[0] << 8) | 0;//G
        pixel[0] = (pixel[0] << 8) | 0;//R
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    }

    void setSunsetColor(){
        pixel[0] = alpha;//A
        pixel[0] = (pixel[0] << 8) | 38;//B
        pixel[0] = (pixel[0] << 8) | 145;//G
        pixel[0] = (pixel[0] << 8) | 211;//R
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    }

    void setBlueSky(){
        pixel[0] = alpha;
        pixel[0] = (pixel[0] << 8) | 255;//B
        pixel[0] = (pixel[0] << 8) | 89;//G
        pixel[0] = (pixel[0] << 8) | 0;//R
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
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
