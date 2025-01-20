#include "EventStack.h"

EventStack::EventStack()
{
    iCurrentEventCount = -1; // -1 means it's empty
}

void EventStack::pop()
{
    if(iCurrentEventCount >= 0)
        iCurrentEventCount--;
}

bool EventStack::empty()
{
    if(iCurrentEventCount < 0)
    {
        return 1;
    } else
    {
        return 0;
    }
}

Event EventStack::top()
{
    if(iCurrentEventCount < 0)
    {
        std::cerr << "Attempted access of an empty stack\n";
        exit(139);
    }
    return eventQueue[iCurrentEventCount];
}

void EventStack::push_back(Event inputEvent)
{
    if( iCurrentEventCount < ( iTotalEventCount - 1 ) )
    {
        iCurrentEventCount++;
        eventQueue[iCurrentEventCount] = inputEvent;
    } else
    {
        std::cerr << "Event Queue full!\n";
    }
}