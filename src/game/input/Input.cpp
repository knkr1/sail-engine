#include <iostream>

#include "Input.h"
#include "core/events/EventSystem.h"


#define LOG(x) std::cout << x << std::endl

void Input::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
}

void Input::processStaticInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_X && action == GLFW_PRESS){
        EventSystem::fire("toggleCursor");
    }
    if(key == GLFW_KEY_F11 && action == GLFW_PRESS){
        EventSystem::fire("toggleFullscreen");
    }
}