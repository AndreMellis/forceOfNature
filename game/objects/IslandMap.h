#ifndef ISLAND_MAP_HEADER_
#define ISLAND_MAP_HEADER_

#include <SDL3/SDL.h>
#include <iostream>

#include "SDLTools/TextureHandler.h"
#include "EventStack.h"

class IslandMap
{
private:
    enum MapParts{ MAP_BASE_MAP, MAP_MANGROVES, MAP_REEF, MAP_TREES, MAP_PARTS_COUNT };
    SDL_Texture *arrIslandTextures[MAP_PARTS_COUNT] = {nullptr};

    bool bRenderMangroves, bRenderReef, bRenderTrees;
public:
    IslandMap();

    bool loadTextures(SDL_Renderer *pGameRenderer);
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *rectMap );

    void handleGameEvent( EventStack *pGameEventStack );
};

#endif