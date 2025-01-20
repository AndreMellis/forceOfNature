#ifndef ISLAND_MAP_HEADER_
#define ISLAND_MAP_HEADER_

#include <SDL3/SDL.h>
#include <iostream>

#include "EventStack.h"

class IslandMap
{
private:
    bool bRenderMangroves, bRenderBuildings, bRenderCorals;
    bool bRenderFracking, bRenderDams;
    bool bRenderForest;
public:
    IslandMap();

    bool loadTextures(SDL_Renderer *pGameRenderer);
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *rectMap );

    void handleGameEvent( EventStack *pGameEventStack );
};

#endif