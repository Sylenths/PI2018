/// \brief Représentation d'une matrice.
/// \details Matrice 4 x 4 utilisable par OpenGL.
/// \author Samuel Labelle
/// \date 30 Mars 2018
/// \version 0.2
/// \warning Matrix ne possèdes pas de constructeur de copie.
/// \bug Aucuns.

#ifndef MATRIX_H
#define MATRIX_H

#include "MathUtils.h"

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


struct Matrix{
    double *matrix;

    /*
     2x2 Matrix cell name reference
    	| a b |
    	| c d |
    */
    /// Déterminant d'une matrice de dimensions 2 x 2.
    /// \param a Case [1, 1] de la matrice.
    /// \param b Case [1, 2] de la matrice.
    /// \param c Case [2, 1] de la matrice.
    /// \param d Case [2, 2] de la matrice.
    /// \return Déterminant de la matrice 2 x 2.
    double det22(double& a, double& b, double& c, double& d) {
        return a * d - b * c;
    }

    /// Constructeur.
    Matrix(){
        matrix = new double[16];
    }

    /// Destructeur.
    ~Matrix(){
        delete[] matrix;
    }

    /// Charge la matrice identitée.
    void loadIdentity(){
        std::fill(&m11, &m44, 0.);
        m11 = m22 = m33 = m44 = 1.;
    }

    /// Charge une matrice de projection (Utilisé pour définir le frustum).
    /// \param t Distance entre le centre et le haut.
    /// \param r Distance entre le centre et la droite.
    /// \param n Distance de la nearplane.
    /// \param f Distance de la farplane.
    void loadProjection(const double& t, const double& r, const double& n, const double& f){

        m11 = n / r; m12 = 0.   ; m13 = 0.                     ;m14 = 0. ;
        m21 = 0.   ; m22 = n / t; m23 = 0.                     ;m24 = 0. ;
        m31 = 0.   ; m32 = 0.   ; m33 = -(f + n) / (f - n)     ;m34 = -1.;
        m41 = 0.   ; m42 = 0.   ; m43 = (-2. * f * n) / (f - n);m44 = 0. ;

    }

    /// Charge une matrice de vue (utilisé par la Caméra).
    /// \param f Vecteur normalisé pointant vers l'avant.
    /// \param s Vecteur normalisé pointant vers le côté.
    /// \param u Vecteur normalisé pointant vers le haut.
    void loadView(const Vector& f, const Vector& s, const Vector& u){
        m11 = s.x  ; m12 = u.x  ; m13 = -f.x  ;m14 = 0. ;
        m21 = s.y  ; m22 = u.y  ; m23 = -f.y  ;m24 = 0. ;
        m31 = s.z  ; m32 = u.z  ; m33 = -f.z  ;m34 = 0. ;
        m41 = 0.   ; m42 = 0.   ; m43 = 0.    ;m44 = 1. ;
    }

    /*
	void loadAxisRotation(Vector v, double angle){
		double s = sin(degtorad(angle));
		double c = cos(degtorad(angle));
		double _1_c = (1 - c);
		double xy = v.x * v.y;
		double xz = v.x * v.z;
		double yz = v.y * v.z;
		double zs = v.z * s;
		double ys = v.y * s;

		m11 = v.x * v.x * _1_c + c ; m12 = xy * _1_c - zs       ; m13 = xz * _1_c + ys ;
		m21 = xy * _1_c + zs       ; m22 = v.y * v.y * _1_c + c ; m23 = yz * _1_c - v.x * s ;
		m31 = xz * _1_c - ys       ; m32 = yz * _1_c + v.x * s  ; m33 = v.z * v.z * _1_c + c;
		//removing the second "* sin" on the m33 line makes for an interesting bug when rotating around the x axis :p
		m14 = m24 = m34 = m41 = m42 = m43 = 0.; m44 = 1. ;
	}
	*/

    /// Charge une matrice de rotation autour d'un axe arbitraire passant par un point arbitraire.
    /// \param p Point par lequel passe l'axe de rotatation.
    /// \param a Axe de rotation
    /// \param angle Angle de rotation.
    void loadArbitraryRotation(Vector p, Vector a, double angle){

        double u2 = a.x*a.x;
        double v2 = a.y*a.y;
        double w2 = a.z*a.z;
        double c = std::cos(degtorad(angle));
        double _1_c = 1 - c;
        double s = std::sin(degtorad(angle));

        /* Neat trick : to invert the positive rotation direction (aka. "default rotation direction"),
        * invert the plus or minus between the two terms of everything in the 3x3 part of the matrix that isn't on the
        * top-left bottom-right diagonal; this amounts to a matrix transposition in this specific case.
        */
        m11 = u2 + (v2 + w2) * c;
        m12 = a.x*a.y * _1_c + a.z*s;
        m13 = a.x*a.z * _1_c - a.y*s;
        m14 = (p.x*(v2 + w2) + a.x*(p.y*a.y + p.z*a.z)) * _1_c + (p.y*a.z - p.z*a.y)*s;

        m21 = a.x*a.y * _1_c - a.z*s;
        m22 = v2 + (u2 + w2) * c;
        m23 = a.y*a.z * _1_c + a.x*s;
        m24 = (p.y*(u2 + w2) + a.y*(p.x*a.x + p.z*a.z)) * _1_c + (p.z*a.x - p.x*a.z)*s;

        m31 = a.x*a.z * _1_c + a.y*s;
        m32 = a.y*a.z * _1_c - a.x*s;
        m33 = w2 + (u2 + v2) * c;
        m34 = (p.z*(u2 + v2) + a.z*(p.x*a.x + p.y*a.y)) * _1_c + (p.x*a.y - p.y*a.x)*s;

        m41 = m42 = m43 = 0.;
        m44 = 1.;

    }

    /// Charge une matrice de translation.
    /// \param v Vecteur de translation relatif à la position actuelle.
    void loadTranslation(Vector v){

        loadIdentity();

        m14 = v.x;
        m24 = v.y;
        m34 = v.z;
        m11 = m22 = m33 = m44 = 1.;
    }

    /// Charge une rotation autour de l'axe des x, centrée en 0, 0, 0.
    /// \param angle Angle de la rotation.
    void loadXrotation(double angle){
        m11 = m44 = 1.;
        m22 = m33 = cos(degtorad(angle));
        m32 = sin(degtorad(angle));
        m23 = -m32;
        m12 = m13 = m14 = m21 = m24 = m31 = m34 = m41 = m42 = m43 = 0.;
    }

    /// Charge une rotation autour de l'axe des y, centrée en 0, 0, 0.
    /// \param angle Angle de la rotation.
    void loadYRotation(double angle){
        m22 = m44 = 1.;
        m11 = m33 = cos(degtorad(angle));
        m13 = sin(degtorad(angle));
        m31 = -m13;
        m12 = m21 = m32 = m23 = m14 = m24 = m34 = m41 = m42 = m43 = 0.;
    };

    /// Charge une rotation autour de l'axe des z, centrée en 0, 0, 0.
    /// \param angle Angle de la rotation.
    void loadZRotation(double angle){
        m33 = m44 = 1.;
        m11 = m22 = cos(degtorad(angle));
        m21 = sin(degtorad(angle));
        m12 = -m21;
        m13 = m14 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.;
    }

    /// Multiplie un vecteur par la matrice.
    /// \param v Vecteur à multiplier.
    /// \return Vecteur multiplié par la matrice.
    Vector operator*(Vector v){
        return Vector(v.x * m11 + v.y * m21 + v.z * m31 + m14,
                      v.x * m12 + v.y * m22 + v.z * m32 + m24,
                      v.x * m13 + v.y * m23 + v.z * m33 + m34);
    }
};

#endif //MATRIX_H
