#include "ChoiceHandler.h"

ChoiceHandler::ChoiceHandler()
{
    genHungerTree();
    genCoastLineTree();
    genZoningTree();
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
        { -0.10, 0, 0, 0, -25 },
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
        { 0.10, 0.10, 0, -1000, 0 },
        nullptr,
        decFutureRightChild
    );

    arrDecisionTrees[COASTLINE_DECISION_TREE] = parentNode;
}