/// \brief Chronometre
/// \details Chronometre en ticks dont en ms.
/// \author Shelby Versailles, Tai Chen Li
/// \date 5 Avril 2018
/// \version 0.1

#ifndef SOURCE_CHRONO_H
#define SOURCE_CHRONO_H

#define SECONDS 1.0
#define MILISECONDS 1000.0
#define MICROSECONDS 1000000.0

#include <chrono>

class Chrono {
private:
    std::chrono::high_resolution_clock::time_point lastTime; ///< Le temps de référence qu'on utilisera pour la soustraction entre le temps qu'on fera.

public:
    /// Constructeur
    Chrono() {
        lastTime = std::chrono::high_resolution_clock::now();
    }

    /// Repartir le chronométrage à zéro
    double restart() {
        lastTime = std::chrono::high_resolution_clock::now();
    }

    /// Obtenir le chronométrage
    /// \param ratio L'unité de mesure voulue au retour du chronométrage
    double getElapsed(int ratio) {
        std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastTime);
        return span.count() * ratio;
    }
};

#endif
