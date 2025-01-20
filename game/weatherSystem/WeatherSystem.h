#ifndef WEATHER_SYSTEM_HEADER_
#define WEATHER_SYSTEM_HEADER_

#include "SDLTools/LTimer.h" // from customCLib
#include "EventStack.h"

class WeatherSystem
{
private:
    LTimer weatherTimer;
    const int iMillisecondsBetweenEvents = .5 * 60 * 1000; // 2.5 mins per event
    const int iMillisecondsBeforeEventLands = 1 * 60 * 1000; // 1 minute warning between event generation and landfall

    bool bHurricaneWasTriggered;
public:
    WeatherSystem();

    void generateEvent( EventStack *pGameEventStack );
};

#endif