# Notes générales

 - Le projet doit être Multi-Plateforme ( Windows, Mac, Linux )

 - 1 tab = 4 espaces

 - Les noms des variables, des fonctions et les commentaires (non destinés à Doxygen) doivent idéalement être en anglais.
 
 - Les commentaires destinés à la documentation par Doxygen devront être en français.
 
 - Les noms de fonctions et de méthodes devraient contenir un verbe à l'infinitif représentatif de l'action effectuée.


# Code

## Ifndef-Define class{/*...*/}; Endif

```C++
#ifndef define...
#ifndef CLASSE_H
#define CLASSE_H

//classe

#endif //CLASSE_H
```

## Includes et Defines

```C++
#define DEFINED_VARIABLE 10

#include <standardLibraryIncludes>

#include "ProjectIncludes.h"
```

## Variables et Fonctions

```C++
int* nomCamelCase;

type nomFonctionCamelCase(type var, type var2) {
    //code
}
````

## Classes

```C++
class NomClasse {
private:
    //code
protected:
    //code
public:
    //code
};
```

## Structures

```C++
struct NomClasse {
    //CODE
};
```

## Switch

```C++
switch(case) {
    case 1:
    	//code
    break;

    default:
    break;
}
```

## If

```C++
if(condition) {
    //code
}
```

## Boucle For
```C++
for(int i = 0; i < 10; ++i) {
    //code
}
```

## Itérateur
```C++
for(auto it : structureDeDonnées) {
    //code
}
```

## Boucle While

```C++
while(condition) {
    //code
}
```

## Doxygen header

```
/// \brief Représentation de matrice à inclure.
/// \details Matrice 4 x 4.
/// \author Antoine Legault et les autres
/// \date 20 février 2018
/// \version 0.1
/// \warning Risque de planter si mal utilisé.
/// \bug Problèmes connus
```
## Doxygen in-code

```
double* matrix; ///< Composante matrix.

/// Multiplication de matrice.
    /// \param v Vecteur multiplicateur.
    /// \return Vecteur résultant de la multiplication.
    Vector3D operator*( const Vector3D& v) const {
        return Vector3D(v.x*m11 + v.y*m21 + v.z*m31 + m41, v.x*m12 + v.y*m22 + v.z*m32 + m42, v.x*m13 + v.y*m23 + v.z*m33 + m43);
    }
    
```

