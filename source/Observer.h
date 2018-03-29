/// \brief Représentation d'un observateur.
/// \details Permet de déclarer un observateur qui réagit aux évènements.
/// \author Antoine Legault, Tai Chen Li, Samuel Labelle
/// \date 28 mars 2018
/// \version 0.1
/// \warning On retourne un bool pour arrêter l'itération dans observable si possible pour sauver du temps de processeur.
/// \bug Aucuns.

#ifndef OBSERVER_H
#define OBSERVER_H

template <typename  T>
class Observer {
public:
    /// Reçoit une notification de l'observable.
    virtual void notify(T arg) = 0;
};


#endif
