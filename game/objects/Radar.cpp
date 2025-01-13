#include "Radar.h"

Radar::Radar()
{
    for(int i = 0 ; i < iTotalWeatherFrames; i++)
    {
        arrNormalWeatherTextures[i] = nullptr;
        arrStormWeatherTextures[i] = nullptr;
    }

    iCountedFrames = 0;
    iCurrentRenderFrame = 0;
}

bool Radar::loadTextures( SDL_Renderer *pGameRenderer )
{
    arrNormalWeatherTextures[0] = TextureHandler::makeTexture( "assets/radar/island.png", pGameRenderer );
    arrNormalWeatherTextures[1] = TextureHandler::makeTexture( "assets/radar/island1.png", pGameRenderer );
    arrNormalWeatherTextures[2] = TextureHandler::makeTexture( "assets/radar/island2.png", pGameRenderer );
    arrNormalWeatherTextures[3] = TextureHandler::makeTexture( "assets/radar/island3.png", pGameRenderer );
    arrNormalWeatherTextures[4] = TextureHandler::makeTexture( "assets/radar/island4.png", pGameRenderer );

    for(int i = 0 ; i < iTotalWeatherFrames; i++)
    {
        if (arrNormalWeatherTextures[i] == nullptr )
        {
            std::cerr << "Failed to load weather textures! SDL_Error: " << SDL_GetError() << "\n";
            return 0;
        }
    }

    return 1;
}

void Radar::render( SDL_Renderer *pGameRenderer, SDL_FRect *rectRadar )
{
    SDL_RenderTexture( pGameRenderer, arrNormalWeatherTextures[iCurrentRenderFrame], NULL, rectRadar );
}

void Radar::tick()
{
    iCountedFrames++;

    switch(iCountedFrames)
    {
        case 30:
            iCurrentRenderFrame = 1;
            break;

        case 60:
            iCurrentRenderFrame = 2;
            break;

        case 90:
            iCurrentRenderFrame = 3;
            break;

        case 120:
            iCurrentRenderFrame = 4;
            break;

        case 150:
            iCurrentRenderFrame = 0;
            iCountedFrames = 0;
    }
}