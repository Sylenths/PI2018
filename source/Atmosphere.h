/// \brief Gestion de l'atmosphère
/// \details Permet de changer l'opacité du filtre et la couleur de l'Atmosphère. Gère aussi le ciel;
/// \author Mathilde Harnois, Guillaume Julien-Desmarchais
/// \date 17 avril 2018
/// \version 0.5
/// \warning
/// \bug Quand alpha passe de 102 (ciel bleu) à 104 (ciel gris) on peut voir le changement de couleur.

#ifndef SOURCE_ATMOSPHERE_H
#define SOURCE_ATMOSPHERE_H


#define ALPHANIGHT 180
#define ALPHADAY 180
#define TRANSITIONTIME 90 //Time for toning down/up alpha
#define HALFTURN 450 //Time for one cycle
#define X1 15  //Start of Toning down alpha (seconds)
#define X3 345 //Start of Toning up alpha   (seconds)


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
    bool dayTime;
    Uint32 *pixel;
    Sky sky;

public:

    Atmosphere(double posx, double posy, double posz, unsigned int textureID, bool rotHitBox, const char* objFile = nullptr) : sky(0.0, 0.0, 0.0,ResourceManager::getTexture("daysky"), ResourceManager::getTexture("nightsky") ,false, "../../models/obj/skysphere.obj"), Model(posx, posy, posz, textureID, rotHitBox, objFile) {
        x2 = X1 + TRANSITIONTIME;
        x4 = X3 + TRANSITIONTIME;
        multiplicator1 = ((-ALPHADAY) / (x2 - X1));
        multiplicator2 = ((ALPHANIGHT) / (x4 - X3));

        b1 = (ALPHADAY - (multiplicator1 * X1));
        b2 = (ALPHANIGHT - (multiplicator2 * x4));
        pixel = new Uint32;

        dayTime = true;
        alpha = 180;//
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
        if(chrono >= X1 && chrono <= x2){//Tone Down alpha to prepare for Night RGBA Colour
            int newAlpha = (multiplicator1 * chrono) + b1;
            if(newAlpha  >= 0)
                alpha = newAlpha;

            updateRGBA();
            return;
        }

        if (chrono >= 106 && chrono <= 110){//Apply night setting ()
            if (dayTime) {
                r = 25;
                g = 25;
                b = 77;
            }return;
        }

        if (chrono >= X3 && chrono <= x4){//Second Half Tone up alpha
            int newAlpha = (multiplicator2 * chrono) + b2;

            if(newAlpha <= 255)
                alpha = newAlpha;

            updateRGBA();
            return;
        }
        if (chrono > HALFTURN){
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
