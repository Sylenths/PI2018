/// \brief Représentation d'un observable.
/// \details Permet de déclarer un observable qui pourra être observé par un observateur.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus
#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"
#include <list>

template <typename T>
class Observable {
private:
    std::list<Observer<T>*> observers;  ///< Liste d'observateurs.

public:
    /// Permettre de s'inscrire à un évènement.
    void subscribe(Observer<T>* observer){
        observers.push_back(observer);
    }

    void unsubscribe(Observer<T>* observer) {
        observers.remove(observer);
    }

    /// Permettre de se faire avertir d'un évènement.
    /// \param arg Entreprendre une action suite à la notification.
    void notify(T arg){
        typename std::list<Observer<T>*>::iterator it = observers.begin();
        for (int i = 0; i <observers.size() ; ++i) {
            (*it++)->notify(arg);
        }

        /*
         * for(auto it : observers*)
         * it->notification;
         */
    }
};


#endif
