#ifndef RISK_HANDLER_HEADER_
#define RISK_HANDLER_HEADER_

#include <SDL3/SDL.h>

class RiskHandler
{
private:
    int iFloodDamagePercentageRisk; // there is an X percent change of a flood happening
    int iHurricaneDamagePercentageRisk; // there is an X percent change of a flood happening
    int iStarvationDamagePercentageRisk; // there is an X percent change of starvation
    int iEarthquakeDamagePercentageRisk; // there is an X percent change of an earthquake risk
    int iTotalRisksToRenderToScreen = 4; // I will use this to track how many bar graphs to render

    // SDL Rects for bar graphs
    SDL_FRect recFloodPerc, recHurricanePerc, recStarvationPerc, recEarthquakePerc;
    SDL_FRect recFloodTotal, recHurricaneTotal, recStarvationTotal, recEarthquakeTotal;

public:
    RiskHandler();

    void tick();
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *dstRec );

};

#endif