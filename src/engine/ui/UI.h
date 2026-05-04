#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "engine/window/Window.h"

class Render;

class UI
{
    Window* window;
    public:
        UI(Window* window) : window(window)
        {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch


            ImGui_ImplGlfw_InitForOpenGL(window->windowObject, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
            ImGui_ImplOpenGL3_Init();
        }
        virtual void startLoop(Render* render){}
        virtual void endLoop(){}
        virtual void terminate(){}
    private:

};