/// \brief Représentation de la lumiere dans l'environnement
/// \details Contient un tableau de réel contenant la position de la lumière
/// \author Patrick Singcaster, Guillaume Julien-Desmarchais
/// \date 16 Avril 2018
/// \version 1.0
#ifndef LIGHT_H
#define LIGHT_H

class Light {
private:
    float position[4];///< Position de la lumière.

public:
    /// Constructeur.
    /// \param x Composante x
    /// \param y Composante y
    /// \param z Composante z
    Light(const float& x, const float& y, const float& z, const float& w) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
        position[3] = w;
    }
    /// Applique la lumière dans notre monde
    void applyLightPosition() {
        glLightfv(GL_LIGHT0, GL_POSITION, position);
    }
    /// Met à jour la position de la lumière
    /// \param x Composante x
    /// \param y Composante y
    /// \param z Composante z
    void update(const float& x, const float& y, const float& z) {
        position[0] = x;
        position[1] = y;
        position[2] = z;
    }
    Vector getVectorLight(){
        return Vector(position[0],position[1],position[2]);
    }

};
#endif
