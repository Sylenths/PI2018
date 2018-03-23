# Notes générales

 - Le projet doit être Multi-Plateforme ( Windows, Mac, Linux )

 - 1 tab = 4 espaces

 - Les noms des variables, des fonctions et les commentaires (non destinés à Doxygen) doivent idéalement être en anglais.
 
 - Les commentaires destinés à la documentation par Doxygen devront être en français.
 
 - Les noms de fonctions et de méthodes devraient contenir un verbe à l'infinitif représentatif de l'action effectuée.

# Doxygen

## En-tête de classe Doxygen (avant Ifndef-Define dans un \*.h)

```C++
/// \brief <Brève description>
/// \details <Description plus détaillée de la classe>
/// \author <Liste des noms auteurs, séparés par une virgule>
/// \date <Date de dernière modification>
/// \version <Version du fichier>
/// \warnings <Avertissements relatifs à l'utilisation de la classe>
/// \bugs <Bugs connnus de la classe>
```

## Description des données membres publiques

```C++
int entier;///< Description courte de la donnée membre.
```

## Description des méthodes publiques
```C++
/// Description courte de la méthode.
/// \param great Description brève du paramètre.
/// \return Description brève du retour de la fonction.
int doSomething(bool great){
    /*...code...*/
    return anAwesomeInt;
}
```
Un `\param` doit être présent pour chaque paramètre de la méthode. Ne pas en mettre si rien n'est passé à la méthode.
`\return` est omis si le type de la méthode est void.

# Code

## Ifndef-Define class{/\*...code...\*/}; Endif

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
```

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
