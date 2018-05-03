/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et sa couleur
/// \author Mathilde Harnois, Guillaume Julien-Desmarchais
/// \date 17 avril 2018
/// \version 0.5
/// \warning Le chrono de projet final doit restart a chaque debut de journée et de nuit
/// \bug

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H

#define MULTIPLICATOR -2  //Modifie le temps de degrader des couleurs de latmosphere Vraie Valeur "-2.666"


#include "includes.h"

class Atmosphere : public Model {
private:
    unsigned int atmosphereTextureId, chrono;
    int r, g, b, alpha;
    Chrono* atmoChrono;
    bool dayTime, cycleChange;
    Uint32 *pixel;
    Sky sky;

public:

    Atmosphere(double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : sky(0.0, 0.0, 0.0,ResourceManager::getInstance()->getTexture("daysky"), ResourceManager::getInstance()->getTexture("nightsky") ,false, "../../models/obj/skysphere.obj"), Model(posx, posy, posz, textureID, rotHitBox, objFile) {
        pixel = new Uint32;
        dayTime = true;
        alpha = 180;
        atmoChrono = new Chrono();
        r = 253;
        g = 150;
        b = 43;
        pixel[0] = alpha;//A
        pixel[0] = (pixel[0] << 8) | b;//B43
        pixel[0] = (pixel[0] << 8) | g;//G150
        pixel[0] = (pixel[0] << 8) | r;//R253

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

    void updateAtmosphereChrono(){

            chrono = atmoChrono->getElapsed(SECONDS);
            sky.rotateSky();
        if(chrono >= 15 && chrono <= 105){//Tone Down alpha
            int newAlpha = (MULTIPLICATOR * chrono) + 210;
            if(newAlpha  >= 0)
                alpha = newAlpha;

            updateRGBA();
            return;
            }


        if (chrono >= 106 && chrono <= 110){//Apply night setting (in middle of day stealth (alpha = 0))
            if (dayTime) {
                r = 25;
                g = 25;
                b = 77;
            }return;
        }

        if (chrono >= 330 && chrono <= 435){//Second Half Tone up alpha
                int newAlpha = (2 * chrono) - 650;

                if(newAlpha <= 255)
                    alpha = newAlpha;

               updateRGBA();
                return;
        }

        if (chrono > 450){
            atmoChrono->restart();
            if (dayTime){
                sky.setNight();
                dayTime = !dayTime;
            }
            else{
                sky.setDay();
                dayTime = !dayTime;
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
        sky.draw();
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
