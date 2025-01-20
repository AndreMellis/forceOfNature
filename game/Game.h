#ifndef GAME_HEADER_
#define GAME_HEADER_

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>

#include "SDLTools/LTimer.h" // from customCLib
#include "RiskHandler.h"
#include "EventStack.h"
#include "IslandMap.h"
#include "Radar.h"

class Game
{
private:
    SDL_Renderer *pGameRenderer;
    SDL_Window *pGameWindow;

    EventStack gameEventStack;
    RiskHandler riskHandler;
    IslandMap islandMap;
    LTimer fpsTimer;
    Radar radar;

    int iWindowWidth, iWindowHeight;
    const int iScreenFPS = 30;
    const int iScreenTicksPerFrame = 1000 / iScreenFPS;

    // I want to hardset cords here for this game
    SDL_FRect rectRadar, rectRisks, rectIslandMap;

    void tick();
    void handleRendering(); // a place to drop all the rendering and leave run clean
    void handleGameEvents(); // handle events on the game stack
    void handleEvents(SDL_Event &event); // a place to drop all the event handling

public:
    Game();

    bool init();
    void run();
    void close();
};

#endif