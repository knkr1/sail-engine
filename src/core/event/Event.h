#pragma once

#include <functional>
#include <vector>

template<typename... Args>
class Event {
public:
    std::vector<std::function<void(Args...)>> listeners;

    void connect(std::function<void(Args...)> listener) {
        listeners.push_back(listener);
    }

    void fire(Args... args) {
        for(auto& listener : listeners) {
            listener(args...);
        }
    }
};