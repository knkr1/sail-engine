#include "EventSystem.h"

std::unordered_map<std::string, std::function<void()>> EventSystem::events;

void EventSystem::on(std::string eventName, std::function<void()> callback)
{
    events[eventName] = callback;
}

void EventSystem::fire(std::string eventName)
{
    if(events.find(eventName) != events.end())
    {
        events[eventName]();
    }
}