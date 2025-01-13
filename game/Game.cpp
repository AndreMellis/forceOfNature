#include "Game.h"


Game::Game()
{
    pGameWindow = nullptr;
    pGameRenderer = nullptr;
}

bool Game::init()
{
    srand(time(0));

    if( SDL_CreateWindowAndRenderer( "Force Of Nature", 1800, 900, SDL_WINDOW_FULLSCREEN, &pGameWindow, &pGameRenderer ) )
    {
        SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
        if( TTF_Init() >= 0 )
        {
            SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );

            // Radar Initialization
            radar.loadTextures( pGameRenderer );
            rectRadar = {
                iWindowWidth * .60f,
                0,
                iWindowWidth * .30f,
                iWindowHeight * .50f
                };

        } else
        {
            std::cerr << "Failed to intialize ttf module! SDL_Error: " << SDL_GetError() << "\n";
            return 0;
        }
    } else
    {
        std::cerr << "Failed to create window and renderer! SDL_Error: " << SDL_GetError() << "\n";
        return 0;
    }

    return 1;
}

void Game::close()
{
    SDL_DestroyRenderer(pGameRenderer);
    SDL_DestroyWindow(pGameWindow);

    pGameRenderer = nullptr;
    pGameWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}


void Game::run()
{
    SDL_Event sdlEvents;
    bool bGameRunning = 1;
    int iCountedFrames = 0;

    SDL_RenderClear(pGameRenderer);
    handleRendering();
    SDL_RenderPresent(pGameRenderer);

    while(bGameRunning)
    {
        fpsTimer.start();

        while( SDL_PollEvent(&sdlEvents) != 0 )
        {
            if( sdlEvents.type == SDL_EVENT_QUIT )
            {
                bGameRunning = 0;
                break;
            } else
            {
                handleEvents(sdlEvents);
            }
        }

        if( !bGameRunning )
            break;

        tick();
        SDL_RenderClear( pGameRenderer );
        handleRendering();
        SDL_RenderPresent( pGameRenderer );

        int iFrameTicks = fpsTimer.getTicks();
        if( iFrameTicks < iScreenTicksPerFrame )
        {
            SDL_Delay( iScreenTicksPerFrame - iFrameTicks );
        }
    }
}

void Game::handleRendering()
{
    radar.render( pGameRenderer, &rectRadar );
}

void Game::handleEvents( SDL_Event &event )
{

}

void Game::tick()
{
    radar.tick();
}