#ifndef RADAR_HEADER_
#define RADAR_HEADER_

#include <SDL3/SDL.h>
#include <iostream>

#include "SDLTools/TextureHandler.h"
#include "SDLTools/LTimer.h"
#include "EventStack.h"

class Radar
{
private:
    const static int iTotalWeatherFrames = 5;

    SDL_Texture *arrNormalWeatherTextures[iTotalWeatherFrames], *arrHurricaneWeatherTextures[iTotalWeatherFrames];
    int iCountedFrames, iCurrentRenderFrame;
    bool bRenderingHurricane;

    SDL_FRect rectWholeScreen;

public:
    Radar();

    bool loadTextures(SDL_Renderer *pGameRenderer);
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *rectRadar );

    void tick();
    void handleGameEvent( EventStack *pGameEventStack );
};

#endif