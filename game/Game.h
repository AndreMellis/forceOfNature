#ifndef GAME_HEADER_
#define GAME_HEADER_

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>

#include "SDLTools/LTimer.h" // from customCLib

class Game
{
private:
    SDL_Renderer *pGameRenderer;
    SDL_Window *pGameWindow;

    LTimer fpsTimer;

    int iWindowWidth, iWindowHeight;
    const int iScreenFPS = 30;
    const int iScreenTicksPerFrame = 1000 / iScreenFPS;

    void tick();
    void handleRendering(); // a place to drop all the rendering and leave run clean
    void handleEvents(SDL_Event &event); // a place to drop all the event handling

public:
    Game();

    bool init();
    void run();
    void close();
};

#endif