#include "Radar.h"

Radar::Radar()
{
    for(int i = 0 ; i < iTotalWeatherFrames; i++)
    {
        arrNormalWeatherTextures[i] = nullptr;
        arrHurricaneWeatherTextures[i] = nullptr;
    }

    iCountedFrames = 0;
    iCurrentRenderFrame = 0;

    bRenderingHurricane = 0;
}

bool Radar::loadTextures( SDL_Renderer *pGameRenderer )
{
    arrNormalWeatherTextures[0] = TextureHandler::makeTexture( "assets/radar/island.png", pGameRenderer );
    arrNormalWeatherTextures[1] = TextureHandler::makeTexture( "assets/radar/island1.png", pGameRenderer );
    arrNormalWeatherTextures[2] = TextureHandler::makeTexture( "assets/radar/island2.png", pGameRenderer );
    arrNormalWeatherTextures[3] = TextureHandler::makeTexture( "assets/radar/island3.png", pGameRenderer );
    arrNormalWeatherTextures[4] = TextureHandler::makeTexture( "assets/radar/island4.png", pGameRenderer );

    arrHurricaneWeatherTextures[0] = TextureHandler::makeTexture( "assets/radar/hurricane1.png", pGameRenderer );
    arrHurricaneWeatherTextures[1] = TextureHandler::makeTexture( "assets/radar/hurricane2.png", pGameRenderer );
    arrHurricaneWeatherTextures[2] = TextureHandler::makeTexture( "assets/radar/hurricane3.png", pGameRenderer );
    arrHurricaneWeatherTextures[3] = TextureHandler::makeTexture( "assets/radar/hurricane4.png", pGameRenderer );
    arrHurricaneWeatherTextures[4] = TextureHandler::makeTexture( "assets/radar/hurricane5.png", pGameRenderer );

    for(int i = 0 ; i < iTotalWeatherFrames; i++)
    {
        if (arrNormalWeatherTextures[i] == nullptr || arrHurricaneWeatherTextures[i] == nullptr )
        {
            std::cerr << "Failed to load weather textures! SDL_Error: " << SDL_GetError() << "\n";
            return 0;
        }
    }

    // sneaking a rect in here
    int iScreenWidth, iScreenHeight;
    SDL_GetRenderOutputSize( pGameRenderer, &iScreenHeight, &iScreenHeight);
    rectWholeScreen = { 0, 0, (float)iScreenWidth, (float)iScreenHeight };

    return 1;
}

void Radar::render( SDL_Renderer *pGameRenderer, SDL_FRect *rectRadar )
{
    if( bRenderingHurricane )
    {
        SDL_RenderTexture( pGameRenderer, arrHurricaneWeatherTextures[iCurrentRenderFrame], NULL, rectRadar );

        if( iCurrentRenderFrame %2 )
        {
            SDL_SetRenderDrawBlendMode( pGameRenderer, SDL_BLENDMODE_BLEND ); //enable alpha on next thing I draw
            SDL_SetRenderDrawColor( pGameRenderer, 233, 48, 48, (255 * .60) );
            SDL_RenderFillRect( pGameRenderer, &rectWholeScreen );
            SDL_SetRenderDrawBlendMode( pGameRenderer, SDL_BLENDMODE_NONE ); //enable alpha on next thing I draw
        }
        
    } else
    {
        SDL_RenderTexture( pGameRenderer, arrNormalWeatherTextures[iCurrentRenderFrame], NULL, rectRadar );
    }
}

void Radar::tick()
{
    iCountedFrames++;

    switch(iCountedFrames)
    {
        case 20:
            iCurrentRenderFrame = 1;
            break;

        case 40:
            iCurrentRenderFrame = 2;
            break;

        case 60:
            iCurrentRenderFrame = 3;
            break;

        case 80:
            iCurrentRenderFrame = 4;
            break;

        case 100:
            iCurrentRenderFrame = 0;
            iCountedFrames = 0;
    }
}

void Radar::handleGameEvent( EventStack *pGameEventStack )
{
    if( ! pGameEventStack->empty()  )
    {
        switch( pGameEventStack->top().eventType )
        {
            case HURRICANE_STARTED_EVENT:
                bRenderingHurricane = 1;
                break;
        }
    }
}