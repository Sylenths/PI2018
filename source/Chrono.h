/// \brief Chronometre
/// \details Chronometre en ticks dont en ms.
/// \author Shelby Versailles
/// \date 5 Avril 2018
/// \version 0.1

#ifndef SOURCE_CHRONO_H
#define SOURCE_CHRONO_H

#include <chrono>

class Chrono {
private:
    std::chrono::high_resolution_clock::time_point lastTime;

public:
    Chrono(){
        lastTime = std::chrono::high_resolution_clock::now();
    }

    double restart() {
        lastTime = std::chrono::high_resolution_clock::now();
    }

    double getElapsed(){
        std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastTime);
        return span.count() * 10000;
    }
};

#endif
