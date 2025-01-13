#ifndef RADAR_HEADER_
#define RADAR_HEADER_

#include <SDL3/SDL.h>
#include <iostream>

#include "SDLTools/TextureHandler.h"

class Radar
{
private:
    const static int iTotalWeatherFrames = 5;
    const static int iTotalStormFrames = 5;

    SDL_Texture *arrNormalWeatherTextures[iTotalWeatherFrames], *arrStormWeatherTextures[iTotalStormFrames];
    int iCountedFrames, iCurrentRenderFrame;

public:
    Radar();

    bool loadTextures(SDL_Renderer *pGameRenderer);
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *rectRadar );

    void tick();
};

#endif