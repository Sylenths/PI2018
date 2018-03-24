/// \brief Représentation d'un observateur.
/// \details Permet de déclarer un observateur qui réagit aux évènements.
/// \author Antoine Legault
/// \date 24 mars 2018
/// \version 0.1
/// \warning Mettre les warning si nécessaire.
/// \bug Problèmes connus

#ifndef OBSERVER_H
#define OBSERVER_H

template <typename  T>
class Observer {
public:
    /// Notifier les observateurs pour un type d'évènement.
    virtual void notification(T arg) = 0;

};


#endif
