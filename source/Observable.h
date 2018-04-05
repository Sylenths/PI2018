/// \brief Représentation d'un observable.
/// \details Permet de déclarer un observable qui pourra être observé par un observateur.
/// \author Antoine Legault, Samuel Labelle
/// \date 24 mars 2018
/// \version 0.1
/// \warning Aucuns.
/// \bug Aucuns
#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer.h"

template <typename T>
class Observable {
private:
    std::list<Observer<T>*> observers;  ///< Liste d'observateurs.

public:
    /// Permet de s' inscrire à la liste de notification.
    /// \param observer Observateur
    void subscribe(Observer<T>* observer){
        observers.push_back(observer);
    }
    /// Permet de se désinscrire de la liste de notification.
    /// \param observer Observateur
    void unsubscribe(Observer<T>* observer) {
        int i = observers.size();
        observers.remove(observer);
    }
    void unsuscribeAll(){
        observers.clear();
    }

    /// Permettre de se faire notifier par l'Observable.
    /// \param arg Paramètre à passer lors de la notification.
    void notify(T arg){
        typename std::list<Observer<T>*>::iterator it = observers.begin();
        for (int i = 0; i < observers.size() ; ++i) {
            (*it++)->notify(arg);
        }
    }
};


#endif
