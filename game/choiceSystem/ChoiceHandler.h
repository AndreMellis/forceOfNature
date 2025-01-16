#ifndef CHOICE_HANDLER_HEADER
#define CHOICE_HANDLER_HEADER


struct RiskResults
{
    float fFloodRiskChange;
    float fHurricaneRiskChange;
    float fEarthquakeRiskChange;
    float fStarvationRiskChange;
    float fMoneyChange;
    float fHappinessChange;
};

struct Decision 
{
    const char *strDescription, *strLeftChildDesc, *strRightChildDesc;
    RiskResults rrLeftChoiceResults, rrRightChoiceResults;
    Decision *decLeftChild, *decRightChild;
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
    void genCoastLineTree();
    void genZoningTree();
    Decision *constructDecision(const char *strInputDescription, const char *strInputLeftChildDesc, const char *strInputRightChildDesc, RiskResults inputLeftResults, RiskResults inputRightResults, Decision *decInputLeftChild = nullptr, Decision *decInputRightChild = nullptr);
public:
    ChoiceHandler();
    
    Decision *getRandomDecision(); // grabs the parent node of a random tree
};

#endif