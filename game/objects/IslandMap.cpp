#include "IslandMap.h"

IslandMap::IslandMap()
{
    bRenderMangroves = 1;
    bRenderBuildings = 0;
    bRenderCorals = 1;
    bRenderFracking = 0;
    bRenderDams = 0;
    bRenderForest = 1;
}

bool IslandMap::loadTextures(SDL_Renderer *pGameRenderer)
{
    return 1;
}

void IslandMap::render( SDL_Renderer *pGameRenderer, SDL_FRect *rectMap )
{

}

void IslandMap::handleGameEvent( EventStack *pGameEventStack )
{

}