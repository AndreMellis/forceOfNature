#include "WeatherSystem.h"

WeatherSystem::WeatherSystem()
{
    weatherTimer.start();
}

void WeatherSystem::generateEvent( EventStack *pGameEventStack )
{
    if (bHurricaneWasTriggered && weatherTimer.getTicks() >= iMillisecondsBeforeEventLands )
    {
        pGameEventStack->push_back( { HURRICANE_LANDED_EVENT, {} } );
        weatherTimer.start();
        bHurricaneWasTriggered = 0;

    } else if ( weatherTimer.getTicks() >= iMillisecondsBetweenEvents )
    {
        pGameEventStack->push_back( { HURRICANE_STARTED_EVENT, {} } );
        weatherTimer.start();
        bHurricaneWasTriggered = 1;
    }
}