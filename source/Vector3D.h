
/// \brief Représentation d'un vecteur.
/// \details Vecteur mathématique de 3 composantes.
/// \author Antoine Legault
/// \date 20 février 2018
/// \version 0.1
/// \warning Risque de planter si mal utilisé.
/// \bug Problèmes connus

#ifndef SINGLETON_VECTOR3D_H
#define SINGLETON_VECTOR3D_H

#include "cmath"

class Vector3D {
    public:
        double x; ///< Composante x.
        double y; ///< Composante y.
        double z; ///< Composante z.


        Vector3D(const double& x = 0. , const double& y = 0. , const double& z = 0.){
            this->x = x;
            this->y = y;
            this->z = z;
        }
    /// Norme d'un vecteur.
    /// \return Norme.
        double GetNorm() const {
            return std::sqrt(x*x + y*y + z*z);
        }
        Vector3D(const Vector3D& v){
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }
    /// Normalisation d'un vecteur.
    /// \return Vecteur normalisé.
        Vector3D& Normalize(){
            const double norm = GetNorm();
            x /= norm;
            y /= norm;
            z /= norm;
            return *this;
        }

        /// Sommation de deux Vecteurs.
        /// \param v Deuxième terme de la sommation.
        /// \return Vecteur résultant de la sommation.
        Vector3D operator+(const Vector3D& v) const {
            return Vector3D(x + v.x, y + v.y, z + v.z);
        }
    /// Soustraction de deux Vecteurs.
    /// \param v Deuxième terme de la soustraction.
    /// \return Vecteur résultant de la soustraction.
		 Vector3D operator-(const Vector3D& v) const {
            return Vector3D(x - v.x, y - v.y, z - v.z);
        }
    /// multiplication de deux Vecteurs.
    /// \param v Deuxième terme de la multiplication.
    /// \return Vecteur résultant de la multiplication.
        double operator*(const Vector3D& v) const{
            return (x*v.x + y*v.y + z*v.z);
        }
    /// multiplication d'un vecteur par un scalaire.
    /// \param v Le scalaire.
    /// \return Vecteur résultant de la multiplication par un scalaire.
		 Vector3D operator*(const double& s) const{
            return Vector3D(x*s + y*s + z*s);
        }

    /// Produit vectoriel de deux Vecteurs.
    /// \param v Deuxième terme du produit vectoriel.
    /// \return Vecteur résultant du produit vectoriel.
        Vector3D operator%(const Vector3D& v) const {
            return Vector3D((y * v.z) - (v.y * z), (z * v.x) - (x * v.z), (x * v.y) - (v.x * y));
        }
    };



#endif
