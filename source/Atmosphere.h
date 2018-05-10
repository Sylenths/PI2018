/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et la couleur de l'Atmosphère. Gère aussi le ciel;
/// \author Mathilde Harnois, Guillaume Julien-Desmarchais
/// \date 17 avril 2018
/// \version 0.7
/// \warning
/// \bug

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H


#define ALPHANIGHT 180
#define ALPHADAY 255
#define TRANSITIONTIME 225 //Time for toning down/up alpha
#define HALFTURN 450 //Time for one cycle
#define X1 0  //Start of Toning down alpha (seconds)
#define X3 225 //Start of Toning up alpha   (seconds)


#include <bitset>
#include "includes.h"

class Atmosphere : public Model {
private:
    unsigned int atmosphereTextureId;
    unsigned int r, g, b;
    int x2, x4, b1, b2, alpha;
    int multiplicator1, multiplicator2;
    double chrono;
    Chrono* atmoChrono;
    bool dayTime, changedTextured;
    Uint32 *pixel;
    Sky sky;

public:

    Atmosphere(const std::string& name, double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : sky(name, 0.0, 0.0, 0.0,EntityManager::get<Texture2d*>("daysky")->ID, EntityManager::get<Texture2d*>("nightsky")->ID ,false, "../../models/obj/skysphere.obj"), Model(name, posx, posy, posz, textureID, rotHitBox, objFile) {
        x2 = X1 + TRANSITIONTIME;
        x4 = X3 + TRANSITIONTIME;
        multiplicator1 = ((ALPHADAY) / (x2 - X1));
        multiplicator2 = ((-ALPHANIGHT) / (x4 - X3));

        b1 = (ALPHADAY - (multiplicator1 * x2));
        b2 = (ALPHANIGHT - (multiplicator2 * x4));
        pixel = new Uint32;

        dayTime = true;
        changedTextured = true;
        alpha = 0;//
        atmoChrono = new Chrono();

        r = 34;
        g = 92;
        b = 173;
        pixel[0] = alpha;//A
        pixel[0] = (pixel[0] << 8) | b;//B43
        pixel[0] = (pixel[0] << 8) | g;//G150
        pixel[0] = (pixel[0] << 8) | r;//R253

        glGenTextures(1, &atmosphereTextureId);
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    ~Atmosphere() {
        delete pixel;
        delete atmoChrono;
    }

    void updateAtmosphere(){

        chrono = atmoChrono->getElapsed(SECONDS);
        sky.rotateSky();
        if(chrono >= X1 && chrono <= x2){//Tone Up alpha to prepare for Night
            int newAlpha = (multiplicator1 * chrono) + b1;
            if(newAlpha  <= 255)
                alpha = newAlpha;

            if (changedTextured){
                if (dayTime)
                    changeSkyColorToLight_Blue();
                else
                    changeSkyColorToDark_Orange();
                changedTextured = false;
            }
            updateRGBA();
        }

        else {
            if (!changedTextured) {
                if (dayTime) {
                    sky.setNight();
                    changeSkyColorToDark_Blue();

                } else {
                    sky.setDay();
                    changeSkyColorToLight_Orange();

                }
                dayTime = !dayTime;
                changedTextured = true;
            }

            int newAlpha = (multiplicator2 * chrono) + b2;

            if (newAlpha >= 0)
                alpha = newAlpha;

            updateRGBA();

            if (chrono > HALFTURN) {
                atmoChrono->restart();
                if (!dayTime) {
                    changeSkyColorToDark_Orange();
                } else {
                    changeSkyColorToLight_Orange();
                }
                changedTextured = true;
            }
        }
    }

    void updateRGBA(){
        pixel[0] = alpha;
        pixel[0] = (pixel[0] << 8) | b;//B 38
        pixel[0] = (pixel[0] << 8) | g;//G 145
        pixel[0] = (pixel[0] << 8) | r;//R 211
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    }

    void changeSkyColorToDark_Orange(){
        r = 94;
        g = 41;
        b = 6;
    }

    void changeSkyColorToLight_Orange(){
        r = 147;
        g = 67;
        b = 12;
    }
    void changeSkyColorToLight_Blue(){
        r = 28;
        g = 79;
        b = 150;
    }
    void changeSkyColorToDark_Blue(){
        r = 21;
        g = 56;
        b = 104;
    }

    Light getRealLight(){
        return sky.getLight();
    };

    void draw() {
        sky.draw();
        glBindTexture(GL_TEXTURE_2D, atmosphereTextureId);

        glEnableClientState(GL_VERTEX_ARRAY);
        //glEnableClientState(GL_NORMAL_ARRAY);
        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        //glNormalPointer(GL_DOUBLE, 0, normals);
        //glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_NORMAL_ARRAY);
        //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
};

#endif
