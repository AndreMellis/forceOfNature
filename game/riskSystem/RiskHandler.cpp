#include "RiskHandler.h"

RiskHandler::RiskHandler()
{
    iFloodDamagePercentageRisk = 10; // we will init to 10 percent chance
    iHurricaneDamagePercentageRisk = 10;
    iStarvationDamagePercentageRisk = 10;
    iEarthquakeDamagePercentageRisk = 10;

    recFloodPerc.x = -1; // cheap check for later
}

void RiskHandler::render( SDL_Renderer *pGameRenderer, SDL_FRect *dstRec )
{
    if (recFloodPerc.x == -1)
    { // this is the first time we are rendering
        int iPaddingBetweenColums = 10;
        float fBarGraphWidth = ( dstRec->w + (iPaddingBetweenColums * 2) ) / iTotalRisksToRenderToScreen;

        recFloodTotal = {
            dstRec->x + ( iPaddingBetweenColums / 2 ),
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
    recFloodPerc.y = (recFloodTotal.y + recFloodTotal.h) * iFloodDamagePercentageRisk;
    recFloodPerc.h = ( recFloodTotal.y + recFloodTotal.h ) - recFloodPerc.y;

    // render the empty recs
    SDL_SetRenderDrawColor( pGameRenderer, 192, 192, 192, 225 );
    SDL_RenderFillRect( pGameRenderer, &recFloodTotal );
    SDL_RenderFillRect( pGameRenderer, &recHurricaneTotal );
    SDL_RenderFillRect( pGameRenderer, &recStarvationTotal );
    SDL_RenderFillRect( pGameRenderer, &recEarthquakeTotal );

    // render the percent recs
    SDL_SetRenderDrawColor( pGameRenderer, 106, 192, 189, 225 );
    //SDL_RenderFillRect( pGameRenderer, &recFloodPerc );

}

void RiskHandler::tick()
{

}