#include "IslandMap.h"

IslandMap::IslandMap()
{
    bRenderMangroves = 1;
    bRenderReef = 1;
    bRenderTrees = 1;
}

bool IslandMap::loadTextures(SDL_Renderer *pGameRenderer)
{
    arrIslandTextures[MAP_BASE_MAP] = TextureHandler::makeTexture( "assets/islandMap/islandMap.png", pGameRenderer );
    arrIslandTextures[MAP_MANGROVES] = TextureHandler::makeTexture( "assets/islandMap/mangroves.png", pGameRenderer );
    arrIslandTextures[MAP_REEF] = TextureHandler::makeTexture( "assets/islandMap/reef.png", pGameRenderer );
    arrIslandTextures[MAP_TREES] = TextureHandler::makeTexture( "assets/islandMap/trees.png", pGameRenderer );
    return 1;
}

void IslandMap::render( SDL_Renderer *pGameRenderer, SDL_FRect *rectMap )
{
    SDL_RenderTexture( pGameRenderer, arrIslandTextures[MAP_BASE_MAP], NULL, rectMap );

    if(bRenderTrees)
        SDL_RenderTexture( pGameRenderer, arrIslandTextures[MAP_TREES], NULL, rectMap );

    if(bRenderReef)
        SDL_RenderTexture( pGameRenderer, arrIslandTextures[MAP_REEF], NULL, rectMap );

    if(bRenderMangroves)
        SDL_RenderTexture( pGameRenderer, arrIslandTextures[MAP_MANGROVES], NULL, rectMap );
}

void IslandMap::handleGameEvent( EventStack *pGameEventStack )
{

}