#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#include "game/camera/Camera.h"

class Window
{
    public:
        int width;
        int height;
        const char* title;

        GLFWwindow* windowElement;

        Window(int width, int height, const char* title) : width(width), height(height), title(title) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            windowElement = glfwCreateWindow(width, height, title, NULL, NULL);
            if (windowElement == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                assert(false && "Failed to create GLFW window");
            }
            glfwMakeContextCurrent(windowElement);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                assert(false && "Failed to initialize GLAD");
            }
            std::cout << glGetString(GL_VERSION) << std::endl;
            glEnable(GL_DEPTH_TEST);      
            glViewport(0, 0, width, height);
            glfwSetFramebufferSizeCallback(windowElement, frameBufferSizeCallback);  

            // tell GLFW to capture our mouse
            glfwSetInputMode(windowElement, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        static void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        void setupCallbacks(Camera* cam){
            glfwSetWindowUserPointer(windowElement, cam);
            
            glfwSetScrollCallback(windowElement, [](GLFWwindow* win, double x, double y){
                static_cast<Camera*>(glfwGetWindowUserPointer(win))->ProcessMouseScroll((float)y);
            });
            
            glfwSetCursorPosCallback(windowElement, [](GLFWwindow* win, double x, double y){
                static_cast<Camera*>(glfwGetWindowUserPointer(win))->ProcessMouseMovement(win,x,y);
            });
        }

        bool shouldClose()
        {
            return glfwWindowShouldClose(windowElement);
        }

        void windowLoopEnd()
        {
             glfwSwapBuffers(windowElement);
             glfwPollEvents();
        }
        

    private:
};