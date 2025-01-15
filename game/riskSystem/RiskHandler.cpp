#include "RiskHandler.h"

RiskHandler::RiskHandler()
{
    fFloodDamagePercentageRisk = .10f; // we will init to 10 percent chance
    fHurricaneDamagePercentageRisk = .10f;
    fStarvationDamagePercentageRisk = .10f;
    fEarthquakeDamagePercentageRisk = .10f;

    recFloodPerc.x = -1; // cheap check for later
}

void RiskHandler::render( SDL_Renderer *pGameRenderer, SDL_FRect *dstRec )
{
    if (recFloodPerc.x == -1)
    { // this is the first time we are rendering
        int iPaddingBetweenColums = 10;
        float fBarGraphWidth = ( dstRec->w - (iPaddingBetweenColums * 2) ) / iTotalRisksToRenderToScreen;

        recFloodTotal = {
            dstRec->x,
            dstRec->y + iPaddingBetweenColums,
            fBarGraphWidth,
            dstRec->h - iPaddingBetweenColums - iPaddingBetweenColums
        };
        recFloodPerc = recFloodTotal;

        recHurricaneTotal = {
            recFloodTotal.x + fBarGraphWidth + iPaddingBetweenColums,
            dstRec->y + iPaddingBetweenColums,
            fBarGraphWidth,
            dstRec->h - iPaddingBetweenColums - iPaddingBetweenColums
        };
        recHurricanePerc = recHurricaneTotal;

        recStarvationTotal = {
            recHurricaneTotal.x + fBarGraphWidth + iPaddingBetweenColums,
            dstRec->y + iPaddingBetweenColums,
            fBarGraphWidth,
            dstRec->h - iPaddingBetweenColums - iPaddingBetweenColums
        };
        recStarvationPerc = recStarvationTotal;

        recEarthquakeTotal = {
            recStarvationTotal.x + fBarGraphWidth + iPaddingBetweenColums,
            dstRec->y + iPaddingBetweenColums,
            fBarGraphWidth,
            dstRec->h - iPaddingBetweenColums - iPaddingBetweenColums
        };
        recEarthquakePerc = recEarthquakeTotal;
    }

    // calculate new sizes for graphs
    recFloodPerc.y = (recFloodTotal.y + recFloodTotal.h ) - ( recFloodTotal.y * fFloodDamagePercentageRisk );
    recFloodPerc.h = ( recFloodTotal.y + recFloodTotal.h ) - recFloodPerc.y;

    recHurricanePerc.y = (recHurricaneTotal.y + recHurricaneTotal.h ) - ( recHurricaneTotal.y * fHurricaneDamagePercentageRisk );
    recHurricanePerc.h = ( recHurricaneTotal.y + recHurricaneTotal.h ) - recHurricanePerc.y;

    recStarvationPerc.y = (recStarvationTotal.y + recStarvationTotal.h ) - ( recStarvationTotal.y * fStarvationDamagePercentageRisk );
    recStarvationPerc.h = ( recStarvationTotal.y + recStarvationTotal.h ) - recStarvationPerc.y;

    recEarthquakePerc.y = (recEarthquakeTotal.y + recEarthquakeTotal.h ) - ( recEarthquakeTotal.y * fEarthquakeDamagePercentageRisk );
    recEarthquakePerc.h = ( recEarthquakeTotal.y + recEarthquakeTotal.h ) - recEarthquakePerc.y;

    // render the empty recs
    SDL_SetRenderDrawColor( pGameRenderer, 192, 192, 192, 225 );
    SDL_RenderFillRect( pGameRenderer, &recFloodTotal );
    SDL_RenderFillRect( pGameRenderer, &recHurricaneTotal );
    SDL_RenderFillRect( pGameRenderer, &recStarvationTotal );
    SDL_RenderFillRect( pGameRenderer, &recEarthquakeTotal );

    // render the percent recs
    SDL_SetRenderDrawColor( pGameRenderer, 106, 192, 189, 225 );
    SDL_RenderFillRect( pGameRenderer, &recFloodPerc );
    SDL_RenderFillRect( pGameRenderer, &recHurricanePerc );
    SDL_RenderFillRect( pGameRenderer, &recStarvationPerc );
    SDL_RenderFillRect( pGameRenderer, &recEarthquakePerc );

}

void RiskHandler::tick()
{

}