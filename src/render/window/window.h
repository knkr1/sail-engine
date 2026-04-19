#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#include "game/camera/Camera.h"
#include "game/input/Input.h"
#include "render/imgui/ImGui.h"

#include "core/events/EventSystem.h"

class Window
{
    public:
        int width;
        int height;
        const char* title;

        GLFWwindow* windowElement;
        GLFWmonitor* monitor;
        const GLFWvidmode* mode;
        bool fullScreen = false;

        Window(int width, int height, const char* title, bool fullscreen = false) : width(width), height(height), title(title), fullScreen(fullscreen) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            monitor = glfwGetPrimaryMonitor();
            mode = glfwGetVideoMode(monitor);

            windowElement = glfwCreateWindow(width, height, title, NULL, NULL);
            glfwSetWindowPos(windowElement, (mode->width-width)/2 , (mode->height-height)/2);
            if (windowElement == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();glfwSwapInterval(1);
                assert(false && "Failed to create GLFW window");
            }
            glfwMakeContextCurrent(windowElement);

            //VSYNC fix
            glfwSwapInterval(1);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                assert(false && "Failed to initialize GLAD");
            }
            std::cout << glGetString(GL_VERSION) << std::endl;
            glEnable(GL_DEPTH_TEST);      
            glViewport(0, 0, width, height);
            glfwSetFramebufferSizeCallback(windowElement, frameBufferSizeCallback);  


            //Handle Events
            setupEvents();

            if(fullscreen){
                fullScreen=false;
                EventSystem::fire("toggleFullscreen");
            }

            // tell GLFW to capture our mouse
            //lets try handling it via camera.h
            //glfwSetInputMode(windowElement, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        static void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }


        //No idea how this works but it does so whatever
        //WARNING: IF YOU INITIALIZE THIS AFTER IMGUI, IT WILL BLOCK IMGUI TO WORK!!!!
        void setupCallbacks(Camera* cam){
            glfwSetWindowUserPointer(windowElement, cam);
            
            glfwSetScrollCallback(windowElement, [](GLFWwindow* win, double x, double y){
                static_cast<Camera*>(glfwGetWindowUserPointer(win))->ProcessMouseScroll((float)y);
            });
            
            glfwSetCursorPosCallback(windowElement, [](GLFWwindow* win, double x, double y){
            
                static_cast<Camera*>(glfwGetWindowUserPointer(win))->ProcessMouseMovement(win,x,y);
            });

            glfwSetKeyCallback(windowElement, [](GLFWwindow* win, int key, int scancode, int action, int mods){
                
                Input::processStaticInput(win, key, scancode, action, mods);
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
        
        void pollEvents(){
            glfwPollEvents();
        }

        void setupEvents()
        {   
            EventSystem::on("toggleFullscreen", [this](){
                fullScreen = !fullScreen;
                glfwSetWindowMonitor(windowElement, fullScreen ? monitor : NULL, 0, 0, fullScreen ? mode->width : width, fullScreen ? mode->height : height, mode->refreshRate);
                if(fullScreen){
                    glfwSetWindowMonitor(windowElement, fullScreen ? monitor : NULL, 0, 0, fullScreen ? mode->width : width, fullScreen ? mode->height : height, mode->refreshRate);
                    glViewport(0, 0, mode->width, mode->height);
                }
                else{
                    glfwSetWindowMonitor(windowElement, NULL, (mode->width-width)/2, (mode->height-height)/2, width, height, 0);
                    glViewport(0, 0, width, height);
                }
            });
        }

    private:
};