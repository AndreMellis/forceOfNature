#ifndef RISK_HANDLER_HEADER_
#define RISK_HANDLER_HEADER_

#include <SDL3/SDL.h>

#include "EventStack.h"
#include "Risks.h"

class RiskHandler
{
private:
    float fFloodDamagePercentageRisk; // there is an X percent change of a flood happening
    float fHurricaneDamagePercentageRisk; // there is an X percent change of a flood happening
    float fStarvationDamagePercentageRisk; // there is an X percent change of starvation
    float fEarthquakeDamagePercentageRisk; // there is an X percent change of an earthquake risk
    int iTotalRisksToRenderToScreen = 4; // I will use this to track how many bar graphs to render

    // SDL Rects for bar graphs
    SDL_FRect recFloodPerc, recHurricanePerc, recStarvationPerc, recEarthquakePerc;
    SDL_FRect recFloodTotal, recHurricaneTotal, recStarvationTotal, recEarthquakeTotal;

public:
    RiskHandler();

    void tick();
    void handleGameEvent( EventStack *pGameEventStack );
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *dstRec );

};

#endif