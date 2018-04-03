/// \brief Représentation d'un vecteur.
/// \details Vecteur mathématique de 3 composantes.
/// \author Samuel Labelle
/// \date 30 Mars 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

struct Vector {

	double x;///< Composante x
	double y;///< Composante y
	double z;///< Composante z

    /// Constructeur.
    /// \param x Composante x
    /// \param y Composante y
    /// \param z Composante z
	Vector(const double& x = 0., const double& y = 0., const double& z = 0.) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

    /// Constructeur de copie de vecteur.
    /// \param v Vecteur à copier.
    Vector(const Vector& v) {
      this->x = v.x;
      this->y = v.y;
      this->z = v.z;
    };

    /// Calcule la norme du vecteur.
    /// \return Norme du vecteur.
	double getNorm() const { // return vector's length
		return std::sqrt(x * x + y * y + z * z);
	}

    /// Normalise le vecteur.
    /// \return Vecteur normalisé.
	Vector& normalize() { // make vector be of length 1
		const double norm = getNorm();
		x /= norm;
		y /= norm;
		z /= norm;

		return *this;
	}

    /// Sommation de deux vecteurs.
    /// \param v Deuxième terme de la sommation.
    /// \return Vecteur résultant de la sommation.
	Vector operator+(const Vector &v) const { // vector addition
		return Vector(x + v.x, y + v.y, z + v.z);
	}

    /// Soustraction de deux vecteurs.
    /// \param v Deuxième terme de la soustraction.
    /// \return Vecteur résultant de la soustraction.
	Vector operator-(const Vector &v) const { // vector substraction
		return Vector(x - v.x, y - v.y, z - v.z);
	}
    /// Produit vectoriel (Cross Product) de deux vecteurs.
    /// \param v Second vecteur du produit vectoriel.
    /// \return Vecteur résultant du produit vectoriel.
	Vector operator%(const Vector &v) const { // cross product
		return Vector(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
	}

    /// Produit scalaire (Dot Product) de deux vecteurs.
    /// \param v Second vecteur du produit scalaire.
    /// \return Nombre résultant du produit scalaire.
	double operator*(const Vector &v) const { // dot product
		return x * v.x + y * v.y + z * v.z;
	}
    /// Multiplication des composantes individuelles du vecteur par un scalaire.
    /// \param s Scalaire par lequel multiplier les composantes.
    /// \return Vecteur avec ses composantes multipliées par s.
	Vector operator*(const double &s) const { // scalar multiplication
		return Vector(x * s, y * s, z * s);
	}

    /// Envoie les composantes du vecteur à la sortie standard.
    void printVector(){
      std::cout << "|" << x << " " << y << " " << z << "|" << "\n";
    }
};

#endif
