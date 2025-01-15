#ifndef CHOICE_HANDLER_HEADER
#define CHOICE_HANDLER_HEADER

struct Decision 
{
    const char *strDescription, *strLeftChildDesc, *strRightChildDesc;
    Decision *decLeftChild, *decRightChild;
};

struct RiskResults
{
    float fFloodRiskChange;
    float fHurricaneRiskChange;
    float fEarthquakeRiskChange;
    float fStarvationRiskChange;
    float fMoneyChange;
    float fHappinessChange;
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

    void genHungerTree();
public:
    ChoiceHandler();
    
    Decision *getRandomDecision(); // grabs the parent node of a random tree
};

#endif