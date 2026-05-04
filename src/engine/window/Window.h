#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <functional>

#include "libraries/sailUtil.h"
#include "core/event/Event.h"

enum windowMode
{
    FULLSCREEN,
    BORDERLESS,
    MAXIMIZED,
    WINDOWED,
    MINIMIZED,
};

class Window
{
    public:
        std::string windowTitle;    
        unsigned int width,height;

        int prevX, prevY, prevWidth, prevHeight;

        windowMode currentWindowMode = MAXIMIZED;
        windowMode windowModeBeforeFullscreen = MAXIMIZED;

        GLFWwindow* windowObject;
        GLFWmonitor* monitor;

        std::function<void(GLFWwindow*,double, double)> mouse_callback;
        std::function<void(GLFWwindow*, int, int, int , int )> input_callback;

        //it's false for the toggle of first call
        bool captureMouse = false;

        Window(){}

        Window(std::string windowTitle, unsigned int width = 800, unsigned int height = 600) : windowTitle(windowTitle), width(width), height(height)
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

            monitor = glfwGetPrimaryMonitor();
            windowObject = glfwCreateWindow(this->width, this->height, this->windowTitle.c_str(), NULL, NULL);

            //Bring it to the middle of the screen
            //GLFWvidmode basically contains the width and height we need (also refreshrate as dessert)
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowPos(windowObject,mode->width/2-(width/2),mode->height/2-(height/2));
            LOG("Refresh rate: "<< mode->refreshRate);

            if (windowObject == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                //TODO: make an universal terminate state so program wont run.
                std::abort();
            }
            glfwMakeContextCurrent(windowObject);
            glfwSwapInterval(1);  // 1 = vsync on, 0 = off

            //Set window's pointer to this class
            //Many code depend on this, be careful
            glfwSetWindowUserPointer(windowObject, this);

            //Frame buffer size callback
            glfwSetFramebufferSizeCallback(windowObject, [](GLFWwindow* window, int width, int height) {
                Window* self = (Window*)glfwGetWindowUserPointer(window);
                self->framebuffer_size_callback(window,width,height);
            });
            
            //mouse callback
            glfwSetCursorPosCallback(windowObject, [](GLFWwindow* window, double xpos, double ypos) {
                Window* self = (Window*)glfwGetWindowUserPointer(window);
                self->mouse_callback(window,xpos,ypos);
            });

            glfwSetKeyCallback(windowObject, [](GLFWwindow* window, int key, int scancode, int action, int mods){
                Window* self = (Window*)glfwGetWindowUserPointer(window);
                self->input_callback(window,key,scancode,action,mods);
            });

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                std::abort();
            }    
            glEnable(GL_DEPTH_TEST);  
            setWindowMode(currentWindowMode);
        }

        void toggleCaptureMouse()
        {
            if(captureMouse==true)
            {
                glfwSetInputMode(windowObject, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                captureMouse = false;  
            }   
            else
            {
                glfwSetInputMode(windowObject, GLFW_CURSOR, GLFW_CURSOR_DISABLED);      
                captureMouse = true;    
            }
            
        }

        void setWindowMode(windowMode mode)
        {
            currentWindowMode = mode;
            const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            if(mode == FULLSCREEN)
            {
                glfwGetWindowPos(windowObject, &prevX, &prevY);
                glfwGetWindowSize(windowObject, &prevWidth, &prevHeight);

                glfwSetWindowMonitor(windowObject, glfwGetPrimaryMonitor(), 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
            }
            else if(mode == BORDERLESS)
            {
                glfwGetWindowPos(windowObject, &prevX, &prevY);
                glfwGetWindowSize(windowObject, &prevWidth, &prevHeight);

                glfwSetWindowAttrib(windowObject, GLFW_DECORATED, GLFW_FALSE);
                glfwSetWindowSize(windowObject, vidmode->width, vidmode->height);
                glfwSetWindowPos(windowObject, 0, 0);
            }
            else if(mode == MAXIMIZED)
            {
                glfwMaximizeWindow(windowObject);
            }
            else if(mode == MINIMIZED)
            {
                glfwIconifyWindow(windowObject);
            }
            else if(mode == WINDOWED)
            {
                glfwSetWindowAttrib(windowObject, GLFW_DECORATED, GLFW_TRUE);
                glfwSetWindowMonitor(windowObject, nullptr, prevX, prevY, prevWidth, prevHeight, 0);
            }
        }
        

        void terminate()
        {
            glfwTerminate();
        }

    private:
        void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            this->width=width;
            this->height=height;
            glViewport(0, 0, width, height);
        }
};