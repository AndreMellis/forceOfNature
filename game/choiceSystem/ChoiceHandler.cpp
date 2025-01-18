#include "ChoiceHandler.h"

Decision::~Decision()
{
    if(decLeftChild)
        delete decLeftChild;

    if(decRightChild)
        delete decRightChild;
}

ChoiceHandler::ChoiceHandler()
{
    genHungerTree();
    genCoastLineTree();
    genZoningTree();

    iLastTreeTaken = -1;
    gameTimer.start();

    choiceFont = nullptr;
    renderingDecisionTexture = nullptr;
}

Decision *ChoiceHandler::constructDecision(const char *strInputDescription, const char *strInputLeftChildDesc, const char *strInputRightChildDesc, RiskResults inputLeftResults, RiskResults inputRightResults, Decision *decInputLeftChild, Decision *decInputRightChild)
{
    Decision *decToReturn = new Decision(
        strInputDescription,
        strInputLeftChildDesc,
        strInputRightChildDesc,
        inputLeftResults,
        inputRightResults,
        decInputLeftChild,
        decInputRightChild
    );

    return decToReturn;
}

void ChoiceHandler::genZoningTree()
{
    Decision *decFutureChild = constructDecision(
        "Hear me out. Skyscrapers! The people demand more space",
        "No",
        "Invade the skies!",
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0.10, 0, 0, 0.10 },
        nullptr,
        nullptr
    );

    Decision *parentNode = constructDecision(
        "What are smelt? fish??? Dam those fish",
        "Leave the fish alone",
        "Build the dams!",
        { 0, 0, 0, 0, 0, 0 },
        { -0.10, 0, 0, 0, -1000, -10 },
        decFutureChild,
        decFutureChild
    );

    decFutureChild = parentNode;
    parentNode = constructDecision(
        "Fracking, Fracking, Fraking. I love that word, let's frack it up",
        "No",
        "frack for oil",
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0.10, 0, 1000, -10 },
        decFutureChild,
        decFutureChild
    );

    decFutureChild = parentNode;
    parentNode = constructDecision(
        "Gutters and sewers, gutters and sewers, why don't we have any gutters or sewers?",
        "Water Evaporates",
        "Let's build some drainage",
        { 0, 0, 0, 0, 0, 0 },
        { -0.25, 0, 0, 0, -1000, -10 },
        decFutureChild,
        decFutureChild
    );

    decFutureChild = parentNode;
    Decision *decFutureChildTwo = constructDecision(
        "I saw other countries offering stilted housing, should we copy that?",
        "no",
        "yes",
        { 0, 0, 0, 0, 0, 0 },
        { -0.10, -0.10, 0, 0, 0, -25 },
        decFutureChild,
        decFutureChild
    );

    parentNode = constructDecision(
        "The people want more space, should we allow the zoning of basements?",
        "No",
        "Yes",
        { 0, 0, 0, 0, 0, 0 },
        { 0.10, 0, 0, 0, 0, 25 },
        decFutureChildTwo,
        decFutureChild
    );

    arrDecisionTrees[ZONING_DECISION_TREE] = parentNode;
}

void ChoiceHandler::genHungerTree()
{
    Decision *decFutureLeftChild = nullptr;
    Decision *decFutureRightChild = nullptr;
    Decision *parentNode = nullptr;

    // setup zone
    parentNode = constructDecision(
        "Now that those stubborn trees are gone, let's zone it up!",
        "More houses",
        "More farms",
        { 0, 0, 0, 0, 1000, 10 },
        { 0, 0, 0, -0.10, 0, 0 },
        nullptr,
        nullptr
    );

    // setup herding
    decFutureLeftChild = constructDecision(
        "If we can't cut the trees, can we atleast put the farmers to work",
        "No",
        "Yes",
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, -0.10, 0, 0 },
        nullptr,
        nullptr
    );

    // setup tree cutting
    decFutureRightChild = parentNode;
    parentNode = constructDecision(
        "Look at all the land being wasted by all those trees",
        "Leave them alone",
        "Get rid of them",
        { 0, 0, 0, 0, 0, 0 },
        { -0.01, 0, 0, 0, 0, -0.05 },
        decFutureLeftChild,
        decFutureRightChild
    );

    // All Done
    arrDecisionTrees[HUNGER_DECISION_TREE] = parentNode;
    decFutureLeftChild = nullptr;
    decFutureRightChild = nullptr;
    decFutureLeftChild = nullptr;
}

void ChoiceHandler::genCoastLineTree()
{
    Decision *decFutureLeftChild = nullptr;
    Decision *decFutureRightChild = nullptr;

    // fishery
    decFutureLeftChild = constructDecision(
        "That coral reef is sitting there offering us nothing. Should we start a fishery?",
        "No",
        "Yes",
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0.10, 0, -0.10, 100, 100 },
        nullptr,
        nullptr
    );

    Decision *parentNode = constructDecision(
        "The hotel guests wish there was more to do",
        "Let them twiddle their thumbs",
        "Go invade the reefs",
        { 0, 0, 0, 0, 0, 0 },
        { 0, 0.10, 0, 0, 1000, 100 },
        decFutureLeftChild,
        nullptr
    );

    decFutureLeftChild = nullptr;
    decFutureRightChild = parentNode;

    //hotels v housing
    parentNode = constructDecision(
        "Now that those stubborn trees are gone, how should we use the land?",
        "Walls, walls to stop the hurricanes",
        "I heard Americans have a lot of money",
        { 0, -0.10, 0, 0, -1000, 0 },
        { 0, 0.10, 0, 0, 0, 0 },
        nullptr,
        decFutureRightChild
    );

    decFutureRightChild = parentNode;
    parentNode = constructDecision(
        "All those trees are ruining my lovely ocean view. What should we do?",
        "Leave them Alone",
        "Cut them down",
        { 0, 0, 0, 0, 0, 0 },
        { 0.10, 0.10, 0, 0, -1000, 0 },
        nullptr,
        decFutureRightChild
    );

    arrDecisionTrees[COASTLINE_DECISION_TREE] = parentNode;
}

Decision *ChoiceHandler::getRandomDecision()
{
    iLastTreeTaken = rand() % DECISION_TREE_COUNT;
    return arrDecisionTrees[iLastTreeTaken];
}

void ChoiceHandler::makeDecision( bool bLeftRight, EventStack *pGameEventStack )
{
    if(iLastTreeTaken < 0 || iLastTreeTaken >= DECISION_TREE_COUNT)
        return; // avoid going out of bounds

    Decision *decToPutOnTop;

    if( iLastTreeTaken == ZONING_DECISION_TREE )
    { // only this one is not a tree
        decToPutOnTop = arrDecisionTrees[iLastTreeTaken]->decLeftChild;
        if( !bLeftRight )
        {
            pGameEventStack->push_back( { DECISION_MADE_EVENT, arrDecisionTrees[iLastTreeTaken]->rrLeftChoiceResults } );
        } else
        {
            pGameEventStack->push_back( { DECISION_MADE_EVENT, arrDecisionTrees[iLastTreeTaken]->rrRightChoiceResults } );
        }

        arrDecisionTrees[iLastTreeTaken]->decLeftChild = nullptr;
        arrDecisionTrees[iLastTreeTaken]->decRightChild = nullptr;

    } else
    {
        if( !bLeftRight )
        {  // we made the left decision
            pGameEventStack->push_back( { DECISION_MADE_EVENT, arrDecisionTrees[iLastTreeTaken]->rrLeftChoiceResults } );

            decToPutOnTop = arrDecisionTrees[iLastTreeTaken]->decLeftChild;
            arrDecisionTrees[iLastTreeTaken]->decLeftChild = nullptr;
        } else
        { // we made a right decision
            pGameEventStack->push_back( { DECISION_MADE_EVENT, arrDecisionTrees[iLastTreeTaken]->rrRightChoiceResults } );

            decToPutOnTop = arrDecisionTrees[iLastTreeTaken]->decRightChild;
            arrDecisionTrees[iLastTreeTaken] = nullptr;
        }
    }

    delete arrDecisionTrees[iLastTreeTaken];
    arrDecisionTrees[iLastTreeTaken] = decToPutOnTop;

    SDL_DestroyTexture(renderingDecisionTexture);
    SDL_DestroyTexture(renderingDecisionLeftOption);
    SDL_DestroyTexture(renderingDecisionRightOption);
    iLastTreeTaken = -1;
}

void ChoiceHandler::generateEvent( SDL_Renderer *pGameRenderer )
{
    // hard coding the box because I'm lazy
    int iWindowWidth, iWindowHeight;
    int iBoxLen = SDL_GetRenderOutputSize( pGameRenderer, &iWindowWidth, &iWindowHeight );

    if( gameTimer.getTicks() >= iMillisecondsBetweenDecisions )
    { // time for a decision
        getRandomDecision();
        
        if( arrDecisionTrees[iLastTreeTaken] == nullptr )
        {
            gameTimer.start();
            return; // cheap way to break out 
        }


        SDL_DestroyTexture(renderingDecisionTexture); // pop the last text out the heap
        SDL_DestroyTexture(renderingDecisionLeftOption); // pop the last text out the heap
        SDL_DestroyTexture(renderingDecisionRightOption); // pop the last text out the heap

        renderingDecisionTexture = TextureHandler::renderTextureFromFontWrapped( arrDecisionTrees[iLastTreeTaken]->strDescription,
                                                                                (iWindowWidth * 0.33f) - 10,
                                                                                choiceFont, 
                                                                                pGameRenderer,
                                                                                {255, 255, 255, 255}, //white
                                                                                &fRenderedWidth,
                                                                                &fRenderedHeight
                                                                                );

        renderingDecisionLeftOption = TextureHandler::renderTextureFromFontWrapped( arrDecisionTrees[iLastTreeTaken]->strLeftChildDesc,
                                                                                (iWindowWidth * 0.33f) - 10,
                                                                                choiceFont, 
                                                                                pGameRenderer,
                                                                                {255, 255, 255, 255}, //white
                                                                                &fLeftOptionWidth,
                                                                                &fLeftOptionHeight
                                                                                );

        renderingDecisionRightOption = TextureHandler::renderTextureFromFontWrapped( arrDecisionTrees[iLastTreeTaken]->strRightChildDesc,
                                                                                (iWindowWidth * 0.33f) - 10,
                                                                                choiceFont, 
                                                                                pGameRenderer,
                                                                                {255, 255, 255, 255}, //white
                                                                                &fRightOptionWidth,
                                                                                &fRightOptionHeight
                                                                                );

                                            
        gameTimer.start(); // restart the timer
    }
}

bool ChoiceHandler::loadFonts()
{
    choiceFont = TTF_OpenFont( "assets/fonts/rye.ttf", 20 );

    if(choiceFont)
    {
        return 1;
    } else
    {
        std::cerr << "Failed to load assets/fonts/rye.ttf\n";
        return 0;
    }
}

void ChoiceHandler::render( SDL_Renderer *pGameRenderer, SDL_FRect *rectDecisionWindow )
{
    if( renderingDecisionTexture && iLastTreeTaken >= 0 )
    { // we are actively making a decision
        SDL_FRect rectDst = {
            rectDecisionWindow->x,
            rectDecisionWindow->y,
            fRenderedWidth,
            fRenderedHeight
        };

        rectLeftOpt = {
            rectDecisionWindow->x,
            (rectDecisionWindow->y + rectDecisionWindow->h) - (fLeftOptionHeight * 2),
            fLeftOptionWidth,
            fLeftOptionHeight
        };

        rectRightOpt = {
            (rectDecisionWindow->x + rectDecisionWindow->w) - fRightOptionWidth,
            (rectDecisionWindow->y + rectDecisionWindow->h) - fRightOptionHeight,
            fRightOptionWidth,
            fRightOptionHeight
        };


        SDL_RenderTexture( pGameRenderer, renderingDecisionTexture, nullptr, &rectDst );
        SDL_RenderTexture( pGameRenderer, renderingDecisionLeftOption, nullptr, &rectLeftOpt );
        SDL_RenderTexture( pGameRenderer, renderingDecisionRightOption, nullptr, &rectRightOpt );
    }
}

void ChoiceHandler::handleEvents( SDL_Event *event, EventStack *pGameEventStack )
{
    if( event->type == SDL_EVENT_MOUSE_BUTTON_UP && iLastTreeTaken >= 0 )
    {
        float fMouseX, fMouseY;
        SDL_GetMouseState( &fMouseX, &fMouseY );
        SDL_FRect rectMouseClick = { fMouseX, fMouseY, 1, 1 }; // one pixel rect where mouse was clicked

        if( SDL_HasRectIntersectionFloat( &rectMouseClick, &rectLeftOpt ) )
        { // the left option was taken
            makeDecision( 0, pGameEventStack );
        } else if( SDL_HasRectIntersectionFloat( &rectMouseClick, &rectRightOpt ) )
        { // the right option was taken
            makeDecision( 1, pGameEventStack );
        }
    }
}