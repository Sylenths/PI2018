/// \brief Chronometre
/// \details Chronometre en ticks dont en ms.
/// \author Shelby Versailles
/// \date 5 Avril 2018
/// \version 0.1

#ifndef SOURCE_CHRONO_H
#define SOURCE_CHRONO_H

#include <SDL2/SDL.h>
#include <chrono>

// heures, T = std::chrono::hours
// minutes, T = std::chrono::minutes
// secondes, T = std::chrono::seconds
// millisecondes, T = std::chrono::milliseconds
// microsecondes, T = std::chrono::microseconds
// nanosecondes, T = std::chrono::nanoseconds

template <typename T>

class Chrono {
private:
    std::chrono::duration<int, std::ratio<1, 100000000>> startTime;
    std::chrono::duration<int, std::ratio<1, 100000000>> endTime;
    ///<< Contient le nombre de ticks

public:
    Chrono() {
        startTime = std::chrono::system_clock::now();
    }

    /// Donne le temps ecoulé depuis le dernier restart.
    /// \return le temps ecoulé depuis le dernier restart
    unsigned int getTime() {
        endTime = std::chrono::system_clock::now();
        std::chrono::duration<T> elapsedTime = endTime - startTime;
        return elapsedTime;
    }

    /// Redémmare le chronos.
    void restart(){
        startTime = std::chrono::system_clock::now();
    }
};

#endif
