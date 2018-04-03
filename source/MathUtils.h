/// \brief Collection de fonctions et algorithmes mathématiques.
/// \details
/// \author Samuel Labelle
/// \date 2 Avril 2018
/// \version 0.0.1
/// \warnings Aucuns.
/// \bugs Aucuns.

#ifndef MATHUTILS_H
#define MATHUTILS_H

#define _USE_MATH_DEFINES
#include <math.h>

/// Convertis un angle de degrés à radians.
/// \param deg Angle en degrés.
/// \return Angle en radians.
double degtorad(double deg)
{
 // return deg * M_PI / 180.0;
}

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

#endif //MATHUTILS_H
