#pragma once

#include "../UI.h"

class demoUI : public UI
{
    public:
        demoUI(Window* window) : UI(window) {}

        void startLoop(Render* render) override
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::ShowDemoWindow(); //Show Window
        }
        void endLoop() override
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        void terminate() override
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    private:

};