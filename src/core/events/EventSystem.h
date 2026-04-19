#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>

class EventSystem
{
    public:
        static void on(std::string eventName, std::function<void()> callback);
        static void fire(std::string eventName);
    private:
        static std::unordered_map<std::string, std::function<void()>> events; 
};