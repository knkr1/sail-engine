#pragma once

class Render;



class Game {
public:

    std::vector<Object*> objectArray;

    virtual ~Game() {}

    virtual void onStart(Render* render) {}
    virtual void onUpdate() {}
    virtual void input_poll(GLFWwindow* window) {}
    virtual void input_callback(GLFWwindow* w, int key, int scancode, int action, int mods) {}
};