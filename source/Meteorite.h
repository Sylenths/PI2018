


/// \brief Représentation d'une météorite
/// \details Classe contenant toutes les informations relatives à une météorite
/// \author Mickaël Grisé-Roy
/// \date 08 mai 2018
/// \version 0.1
/// \warning
/// \bug
#ifndef SOURCE_METEORITE_H
#define SOURCE_METEORITE_H
#include "includes.h"
class Meteorite : public Model{
private:

    double radius;///< Le rayon de la météorite
    Vector centerPos;///<La position du centre de la météorite
    Vector speed;///< Le vecteur vitesse de la météorite
    Chrono time;///< Indique le temps écoulé entre chaque rafaichissement d'écran


public:
    /// Constructeur
    /// \param radius Le rayon du météore
    /// \param centerPos Le point central de la sphere
    /// \param initialSpeed Le vecteur vitesse initial
    /// \param textureID L'ID OGL de
    /// \param objfile
    Meteorite( double radius, Vector centerPos, Vector initialSpeed, unsigned int textureID = EntityManager::get<Texture2d *>("meteorite")->ID,const char* objfile = "../../models/obj/meteorite.obj" ) : Model("",centerPos.x, centerPos.y, centerPos.z, textureID, false,objfile) {
        this->radius = radius;
        this->speed = initialSpeed;
        this->centerPos = centerPos;
        Matrix matrix;
        matrix.loadTranslation(-centerPos);
        transform(matrix);
        matrix.loadScaling(radius,radius,radius);
        transform(matrix);
        matrix.loadTranslation(centerPos);
        transform(matrix);
        time.restart();
    }
    void draw(){
        double dt = time.getElapsed(SECONDS);
        speed.y = speed.y - (GRAVITY * dt);
        Vector shifting = centerPos;
        centerPos =centerPos + (speed * dt);
        shifting = centerPos - shifting;
        Matrix matrix;
        matrix.loadTranslation(shifting);
        transform(matrix);
        time.restart();

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


};
#endif //SOURCE_METEORITE_H
