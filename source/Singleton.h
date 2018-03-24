
/// \brief Représentation d'une instance utilisable partout.
/// \details Permet de se déclarer une variable ou une classe en global.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
private:
    static T* instance;     ///< Composante instance.
public:
    /// Récupérer l'instance.
    static T* getInstance(){
        if(!instance)
            instance = new T();
        return instance;
    }
};
template <typename T>
T* Singleton<T>::instance = NULL;


#endif
