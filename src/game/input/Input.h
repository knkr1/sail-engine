#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Input 
{
    static void processInput(GLFWwindow* window);
    static void processStaticInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};