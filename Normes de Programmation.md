# Notes générales

 - Le projet doit être Multi-Plateforme ( Windows, Mac, Linux )

 - 1 tab = 4 espaces

 - Les noms des variables, des fonctions et des commentaires (non destinés à doxygen) en anglais doivent:
    - Idéalement, contenir un verbe à l'infinitif.
    - Être en anglais.

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

````C++
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

