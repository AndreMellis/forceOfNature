#ifndef EVENT_STACK_HEADER_
#define EVENT_STACK_HEADER_

#include <iostream>
#include "Risks.h"

enum EventType
{
    DECISION_MADE_EVENT,
    TOTAL_EVENT_TYPE_COUNT
};

struct Event
{
    EventType eventType;
    RiskResults risksResults = {0, 0, 0, 0, 0, 0}; // initialize to null just incase
};

class EventStack
{
private:
    static const int iTotalEventCount = 5; // picked arbitrarily
    int iCurrentEventCount;

    Event eventQueue[iTotalEventCount];
public:
    EventStack();

    void push_back( Event inputEvent );
    void pop();
    bool empty();
    Event top();
};

#endif