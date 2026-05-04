#pragma once

#include "../UI.h"
#include "engine/Render.h"

class testUI : public UI
{
    public:
        Render* render;
        testUI(Window* window) : UI(window) {}

        void frame()
        {   
            ImGui::Begin("Controls");
            ImGui::SliderFloat("Ambient Strength", &render->ambientStrength, 0.0f, 1.0f);
            ImGui::ColorEdit4("World Light Color", glm::value_ptr(render->worldLightColor));
            ImGui::End();
        }

        void startLoop(Render* r) override
        {
            render = r;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            frame();
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