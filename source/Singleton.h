/// \brief Représentation d'une instance unique utilisable partout.
/// \details Permet de déclarer une instance unique globale.
/// \author Antoine Legault, Samuel Labelle
/// \date 27 mars 2018
/// \version 0.2

#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
private:
    static T* instance; ///< Pointeur vers l'instance.
public:
    /// Récupérer l'instance.
    static T* getInstance(){
        if(!instance)
            instance = new T();
        return instance;
    }

	/// Effacer l'instance.
    static void deleteInstance() {
      delete instance;
    }
};
template <typename T>
T* Singleton<T>::instance = NULL;

#endif
