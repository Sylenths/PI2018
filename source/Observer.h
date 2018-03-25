/// \brief Représentation d'un observateur.
/// \details Permet de déclarer un observateur qui réagit aux évènements.
/// \author Antoine Legault, Tai Chen Li
/// \date 24 mars 2018
/// \version 0.1
/// \warning On retourne un bool pour arrêter l'itération dans observable si possible pour sauver du temps de processeur.
/// \bug Problèmes connus

#ifndef OBSERVER_H
#define OBSERVER_H

template <typename  T>
class Observer {
public:
    /// Notifier les observateurs pour un type d'évènement.
    virtual bool notify(T arg) = 0;
};


#endif
