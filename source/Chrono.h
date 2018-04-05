/// \brief Chronometre
/// \details Chronometre en ticks dont en ms.
/// \author Shelby Versailles
/// \date 5 Avril 2018
/// \version 0.1

#ifndef SOURCE_CHRONO_H
#define SOURCE_CHRONO_H

#include <SDL2/SDL.h>

class Chrono{
private:
    unsigned int ticks; ///<< Contient le nombre de ticks

public:
    Chrono(){
        ticks = SDL_GetTicks();
    }

    /// Donne le temps ecoulé depuis le dernier restart.
    /// \return le temps ecoulé depuis le dernier restart
    unsigned int getTime(){
        return SDL_GetTicks()-ticks;
    }

    /// Redémmare le chronos.
    void restart(){
        ticks = SDL_GetTicks();
    }
};

#endif
