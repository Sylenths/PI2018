/// \brief Gestion du ciel.
/// \details Permet de tourner le ciel et changer sa texture.
/// \author Mathilde Harnois
/// \date 12 avril 2018
/// \version 0.1
/// \warning
/// \bug La lumiere du monde glisse en bas de l'axe des Y et crée des anomalies, à corriger.

#ifndef SOURCE_SKY_H
#define SOURCE_SKY_H



#include "includes.h"

class Sky : public Model {
private:
    Matrix rotation; ///< Matrice de rotation du ciel
    Chrono* skyChrono;///< Chrono pour la rotation du ciel
    Vector vecteur;///< Représentation de la lumière en vecteur.
    Light worldLight;///< La lumière de notre monde

public:

    /// Contructeur
    /// \param textureID Identificateur de la texture.
    /// \param objFile Nom du fichier depuis lequel charger le modèle, au format Wavefront (.obj).
    Sky(const std::string name, double posx, double posy, double posz, unsigned int textureDay, unsigned int textureNight, bool rotHitBox, const char* objFile = nullptr) : Model(name, posx, posy, posz, textureDay, rotHitBox, objFile), worldLight(500.0,10.0,500.0, 1.0) {
        skyChrono = new Chrono();
        vecteur = {0.0,450.0,0.0};
        textureIDs["night"] =  textureNight;
        textureIDs["day"] = textureDay;
        textureToDraw = textureIDs["day"];
        rotation.loadXrotation(70);
        transform(rotation);
        rotation.loadXrotation(70);
        vecteur = rotation * vecteur;

        rotation.loadXrotation(-0.04);//Rotation de 360* apres 900 secondes (cycle jour-nuit)
    }
    ///Change la texture pour celle de nuit
    void setNight(){
        textureToDraw = textureIDs["night"];
        rotation.loadXrotation(180);
        vecteur = rotation * vecteur;

        rotation.loadXrotation(-0.04);
    }
    ///Change la texture pour celle de nuit
    void setDay(){
        textureToDraw = textureIDs["day"];
        rotation.loadXrotation(180);
        vecteur = rotation * vecteur;
        rotation.loadXrotation(-0.04);
    }
    ///Applique la rotation de la terre
    void rotateSky(){
        if (skyChrono->getElapsed(SECONDS) > 0.1){
            transform(rotation);
            vecteur = rotation * vecteur;
            worldLight.update(vecteur.x,vecteur.y,vecteur.z);
            skyChrono->restart();
        }
    }

    Light getLight(){
        return worldLight;
    }

    void draw(){
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
/*
    /// Change la position de la sphère selon le temps écoulé dans une phase de jeu avec une rotation
    /// \param deltaTime Temps écoulé depuis le dernier calcul d'angle
    void update(Chrono deltaTime) {
        //on considère qu'une phase dure 15 minutes, donc rotationne de 6 degrés par minutes (qu'on converti en microsecondes)
        if(sphereAngle >= 180 && sphereAngle < 360) { //NightTime
            isDayTime = false;
            textureToDraw = textureIDs["nightsky"];
        }
        else {
            if(sphereAngle >= 360) {//DayTime
                isDayTime = true;
                sphereAngle = 0;
                textureToDraw = textureIDs["daysky"];

            }
            else {
                sphereAngle += deltaTime.getElapsed(MICROSECONDS) * (1.00 * pow(10, -7));
                rotation.loadZRotation(sphereAngle);
                //transform(rotation);
            }
        }
    }
     */
};


#endif
