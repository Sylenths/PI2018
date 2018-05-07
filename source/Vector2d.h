#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d {
public:
    double x;///< Composante x
    double y;///< Composante y

    /// Constructeur.
    /// \param x Composante x
    /// \param y Composante y
    Vector2d(const double& x = 0.0, const double& y = 0.0) {
        this->x = x;
        this->y = y;
    }

    /// Constructeur de copie de vecteur.
    /// \param v Vecteur à copier.
    Vector2d(const Vector2d& v) {
      this->x = v.x;
      this->y = v.y;
    }
};

#endif
