/// \brief Chronometre
/// \details Chronometre en ticks dont en ms.
/// \author Shelby Versailles
/// \date 20 février 2018
/// \version 0.1

#ifndef SOURCE_CHRONOS_H
#define SOURCE_CHRONOS_H


#include <SDL2/SDL.h>

class Chronos{
private:
    unsigned int ticks;
public:
    Chronos(){
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

#endif //SOURCE_CHRONOS_H
