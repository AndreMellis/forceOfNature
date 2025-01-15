#include "ChoiceHandler.h"

ChoiceHandler::ChoiceHandler()
{
    genHungerTree();
}

void ChoiceHandler::genHungerTree()
{
    Decision *decFutureLeftChild = nullptr;
    Decision *decFutureRightChild = nullptr;
    Decision *parentNode = nullptr;

    // setup zone
    parentNode = new Decision();
    parentNode->strDescription = "Now that those stubborn trees are gone, let's zone it up!";
    parentNode->strLeftChildDesc = "More houses!";
    parentNode->strRightChildDesc = "More farms!";

    // setup herding
    decFutureLeftChild = new Decision();
    decFutureLeftChild->strDescription = "If we can't cut the trees, can we atleast put the farmers to work";
    decFutureLeftChild->strLeftChildDesc = "No";
    decFutureLeftChild->strRightChildDesc = "Yes";

    // setup tree cutting
    decFutureRightChild = parentNode;
    parentNode = new Decision();
    parentNode->strDescription = "Look at all the land being wasted by all those trees";
    parentNode->strLeftChildDesc = "Leave them alone";
    parentNode->strRightChildDesc = "Get rid of them";
    parentNode->decLeftChild = decFutureLeftChild;
    parentNode->decRightChild = decFutureRightChild;


    // All Done
    arrDecisionTrees[HUNGER_DECISION_TREE] = parentNode;
    decFutureLeftChild = nullptr;
    decFutureRightChild = nullptr;
    decFutureLeftChild = nullptr;
}