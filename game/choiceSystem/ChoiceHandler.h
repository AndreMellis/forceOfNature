#ifndef CHOICE_HANDLER_HEADER
#define CHOICE_HANDLER_HEADER

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <cstdlib>

#include "SDLTools/TextureHandler.h" // from customCLib
#include "SDLTools/LTimer.h" // from customCLib
#include "EventStack.h"
#include "Risks.h"

struct Decision 
{
    const char *strDescription, *strLeftChildDesc, *strRightChildDesc;
    RiskResults rrLeftChoiceResults, rrRightChoiceResults;
    Decision *decLeftChild, *decRightChild;

    ~Decision();
};

class ChoiceHandler
{
private:
    enum DecisionTrees{
        COASTLINE_DECISION_TREE,
        ZONING_DECISION_TREE,
        HUNGER_DECISION_TREE,
        DECISION_TREE_COUNT
    };

    Decision *arrDecisionTrees[DECISION_TREE_COUNT] = {nullptr};
    int iLastTreeTaken;

    LTimer gameTimer;
    const int iMillisecondsBetweenDecisions = 3 * 1000; // one dec per 30 secs

    TTF_Font *choiceFont;
    SDL_Texture *renderingDecisionTexture, *renderingDecisionLeftOption, *renderingDecisionRightOption;
    float fRenderedWidth, fRenderedHeight, fLeftOptionWidth, fLeftOptionHeight, fRightOptionWidth, fRightOptionHeight;
    SDL_FRect rectLeftOpt, rectRightOpt;

    void genHungerTree();
    void genCoastLineTree();
    void genZoningTree();

    Decision *constructDecision(const char *strInputDescription, const char *strInputLeftChildDesc, const char *strInputRightChildDesc, RiskResults inputLeftResults, RiskResults inputRightResults, Decision *decInputLeftChild = nullptr, Decision *decInputRightChild = nullptr);
    Decision *getRandomDecision(); // grabs the parent node of a random tree

    void makeDecision(bool bLeftRight, EventStack *pGameEventStack ); // 0 is left, 1 is right
public:
    ChoiceHandler();

    bool loadFonts();
    void render( SDL_Renderer *pGameRenderer, SDL_FRect *rectDecisionWindow );

    void generateEvent( SDL_Renderer *pGameRenderer );
    void handleEvents( SDL_Event *event, EventStack *pGameEventStack );
};

#endif