#ifndef CHOICE_HANDLER_HEADER
#define CHOICE_HANDLER_HEADER

#include <cstdlib>
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

    void genHungerTree();
    void genCoastLineTree();
    void genZoningTree();
    Decision *constructDecision(const char *strInputDescription, const char *strInputLeftChildDesc, const char *strInputRightChildDesc, RiskResults inputLeftResults, RiskResults inputRightResults, Decision *decInputLeftChild = nullptr, Decision *decInputRightChild = nullptr);
public:
    ChoiceHandler();
    
    Decision *getRandomDecision(); // grabs the parent node of a random tree
    void makeDecision(bool bLeftRight); // 0 is left, 1 is right
};

#endif