#include "Game.h"

Game::Game()
{
    pGameWindow = nullptr;
    pGameRenderer = nullptr;
}

bool Game::init()
{
    srand(time(0));

    if( SDL_CreateWindowAndRenderer( "Force Of Nature", 0, 0, SDL_WINDOW_FULLSCREEN, &pGameWindow, &pGameRenderer ) )
    {
        SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
        if( TTF_Init() >= 0 )
        {
            //SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );
            SDL_SyncWindow( pGameWindow );
            SDL_GetWindowSize( pGameWindow, &iWindowWidth, &iWindowHeight );

            // Texture Initialization
            radar.loadTextures( pGameRenderer );
            islandMap.loadTextures( pGameRenderer );
            choiceHandler.loadFonts();

            // rects
            float fPaddingSize = 5.0f;

            rectRadar = {
                (iWindowWidth * .66f) + fPaddingSize,
                fPaddingSize,
                iWindowWidth - ( iWindowWidth * .66f ) - fPaddingSize,
                iWindowHeight * .50f - fPaddingSize
                };

            rectRisks = {
                0,
                iWindowHeight * .50f,
                iWindowWidth * .33f,
                iWindowHeight * .50f
            };

            rectIslandMap = {
                (iWindowWidth * .66f) + fPaddingSize,
                (iWindowHeight * .50f) + fPaddingSize,
                iWindowWidth - ( iWindowWidth * .66f ) - fPaddingSize,
                iWindowHeight * .50f - fPaddingSize
            };

            rectDecisionWindow = {
                (iWindowWidth * .33f) + fPaddingSize,
                fPaddingSize,
                (iWindowWidth * .33f) - fPaddingSize,
                iWindowHeight * .50f - fPaddingSize
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

    SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
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
                handleEvents(&sdlEvents);
            }
        }

        if( !bGameRunning )
            break;

        tick();
        handleGameEvents();
        SDL_SetRenderDrawColor( pGameRenderer, 0, 0, 0, 255 );
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
    choiceHandler.render( pGameRenderer, &rectDecisionWindow );
    riskHandler.render( pGameRenderer, &rectRisks );
    islandMap.render( pGameRenderer, &rectIslandMap );
    radar.render( pGameRenderer, &rectRadar ); // make this last because red alert
}

void Game::handleEvents( SDL_Event *event )
{
    choiceHandler.handleEvents( event, &gameEventStack );
}

void Game::handleGameEvents()
{
    choiceHandler.generateEvent( pGameRenderer );
    weatherSystem.generateEvent( &gameEventStack );

    while( !gameEventStack.empty() )
    {
        EventType eventLastGameEvent = gameEventStack.top().eventType;

        /*
            HANDLE ALL GAME EVENTS HERE
        */
        riskHandler.handleGameEvent( &gameEventStack );
        islandMap.handleGameEvent( &gameEventStack );
        radar.handleGameEvent( &gameEventStack );

        if( !gameEventStack.empty() && gameEventStack.top().eventType == eventLastGameEvent )
        { // the event stack is not empty and we processed an event that noone removed
            gameEventStack.pop();
        }

    }
}

void Game::tick()
{
    radar.tick();
    riskHandler.tick();
}