/// \brief Représentation de matrice à inclure.
/// \details Matrice 4 x 4.
/// \author Antoine Legault
/// \date 20 février 2018
/// \version 0.1
/// \warning Risque de planter si mal utilisé.
/// \bug Problèmes connus
#ifndef SDLPROJECT_MATRIX_H
#define SDLPROJECT_MATRIX_H

#define m11 matrix[0]
#define m12 matrix[1]
#define m13 matrix[2]
#define m14 matrix[3]
#define m21 matrix[4]
#define m22 matrix[5]
#define m23 matrix[6]
#define m24 matrix[7]
#define m31 matrix[8]
#define m32 matrix[9]
#define m33 matrix[10]
#define m34 matrix[11]
#define m41 matrix[12]
#define m42 matrix[13]
#define m43 matrix[14]
#define m44 matrix[15]

#include "Vector3D.h"

class Matrix {
public:
double* matrix; ///< Création de la matrix.

    Matrix(){
        matrix = new double[16];
    }

    ~Matrix(){
        delete[] matrix;
    }
    /// Loader la matrice de projection.
    /// \param r le coté "r".
    /// \param t le coté "t".
    /// \param n le coté "n".
    /// \param f le coté "f".
     void loadProjection(const double& r, const double& t, const double& n, const double& f){
         m11 = (2*n)/(r + r);       m12 = 0.0;                  m13 = 0.0;                  m14 = 0.0;
         m21 = 0.0;                 m22 = (2*n)/(t + t);        m23 = 0.0;                  m24 = 0.0;
         m31 = 0.0;                 m32 = 0.0;                  m33 = (-(f + n))/(f - n);   m34 = -1;
         m41 = 0.0;                 m42 = 0.0;                  m43 = (-2*f*n)/(f-n);       m44 = 0.0;
     }
    /// Loader la matrice de vue.
    /// \param f le vecteur de devant (front).
    /// \param s le vecteur de coté (side).
    /// \param u le vecteur de dessus (up).
    void loadView(const Vector3D& f, const Vector3D& s, const Vector3D& u){
        m11 = s.x;  m12 = u.x;  m13 = -f.x;  m14 = 0.0;
        m21 = s.y;  m22 = u.y;  m23 = -f.y;  m24 = 0.0;
        m31 = s.z;  m32 = u.z;  m33 = -f.z;  m34 = 0.0;
        m41 = 0.0;  m42 = 0.0;  m43 = 0.0;   m44 = 1.0;

    }
    /// Loader la matrice identité.
     void loadIdentity(){
         m11 = 1.0;  m12 = 0.0;  m13 = 0.0;  m14 = 0.0;
         m21 = 0.0;  m22 = 1.0;  m23 = 0.0;  m24 = 0.0;
         m31 = 0.0;  m32 = 0.0;  m33 = 1.0;  m34 = 0.0;
         m41 = 0.0;  m42 = 0.0;  m43 = 0.0;  m44 = 1.0;
     }

    /// Loader la matrice de roation en x.
    /// \param angle l'inclinaison de l'angle.
    void LoadXRotation(const double& angle){
        double c = cos(angle);
        double s = sin(angle);

        m11 = 1.0;  m12 = 0.0;          m13 = 0.0;          m14 = 0.0;
        m21 = 0.0;  m22 = c;            m23 = -s;           m24 = 0.0;
        m31 = 0.0;  m32 = s;            m33 = c;            m34 = 0.0;
        m41 = 0.0;  m42 = 0.0;          m43 = 0.0;          m44 = 1.0;
    }
    /// Loader la matrice de roation en y.
    /// \param angle l'inclinaison de l'angle.
    void LoadYRotation(const double& angle){
        double c = cos(angle);
        double s = sin(angle);

        m11 = c;            m12 = 0.0;          m13 = s;                   m14 = 0.0;
        m21 = 0.0;          m22 = 1.0;          m23 = 0.0;                 m24 = 0.0;
        m31 = -s;           m32 = 0.0;          m33 = c;                   m34 = 1.0;
        m41 = 0.0;          m42 = 0.0;          m43 = 0.0;                 m44 = 1.0;
    }
    /// Loader la matrice de roation en z.
    /// \param angle l'inclinaison de l'angle.
    void LoadZRotation(const double& angle){
        double c = cos(angle);
        double s = sin(angle);

        m11 = c;            m12 = -s;           m13 = 0.0;          m14 = 0.0;
        m21 = s;            m22 = c;            m23 = 0.0;          m24 = 0.0;
        m31 = 0.0;          m32 = 0.0;          m33 = 1.0;          m34 = 0.0;
        m41 = 0.0;          m42 = 0.0;          m43 = 0.0;          m44 = 1.0;
    }
    /// Loader la matrice de roation ultime.
    /// \param p le vecteur pour le stockage de données.
    /// \param a le vecteur de données.
    /// \param angle l'inclinaison de l'angle.
    void loadRotate(const Vector3D& p, const Vector3D& a, const double& angle){
        Vector3D A(a); A.Normalize();
        double S = std::sin(angle);
        double C = std::cos(angle);
        double IC = 1  - C;

        m11 = A.x * A.x * IC + C;           m12 = A.x * A.y * IC - A.z * S;     m13 = A.x * A.z * IC + A.y * S;     m14 = 0.;
        m21 = A.y * A.x * IC + A.z * S;     m22 = A.y * A.y * IC + C;           m23 = A.y * A.z * IC - A.x * S;     m24 = 0.;
        m31 = A.x * A.z * IC - A.y * S;     m32 = A.y * A.z * IC + A.x * S;     m33 = A.z * A.z * IC + C;           m34 = 0.;
        m41 = p.x;                          m42 = p.y;                          m43 = p.z;                          m44 = 1.;
    }

    /// Multiplication de matrice.
    /// \param v Vecteur multiplicateur.
    /// \return Vecteur résultant de la multiplication.
    Vector3D operator*( const Vector3D& v) const {
        return Vector3D(v.x*m11 + v.y*m21 + v.z*m31 + m41, v.x*m12 + v.y*m22 + v.z*m32 + m42, v.x*m13 + v.y*m23 + v.z*m33 + m43);
    }

};


#endif //SDLPROJECT_MATRIC_H
