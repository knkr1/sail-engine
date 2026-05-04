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
            // Main Controls
            ImGui::Begin("Sail Engine");
            
            if(ImGui::CollapsingHeader("World Properties"))
            {
                ImGui::SliderFloat("Ambient Strength", &render->ambientStrength, 0.0f, 1.0f);
                ImGui::ColorEdit4("World Light Color", glm::value_ptr(render->worldLightColor.color));
                ImGui::ColorEdit4("Background Color", glm::value_ptr(render->gameColor.color));
            }

            if(ImGui::CollapsingHeader("Camera Properties"))
            {
                ImGui::SliderFloat("FOV", &render->camera.fov, 1.0f, 120.0f);
                ImGui::DragFloat3("Position", glm::value_ptr(render->camera.cameraPos), 0.1f);
            }

            if(ImGui::CollapsingHeader("Objects"))
            {
                for(int i = 0; i < render->game->objectArray.size(); i++)
                {
                    Object* obj = render->game->objectArray[i];
                    std::string label;
                    if(obj==render->sun)
                    {
                        label = "Sun";
                    }
                    else{
                        label = "Object " + std::to_string(i);
                    }
                    
                    if(ImGui::TreeNode(label.c_str()))
                    {
                        ImGui::DragFloat3("Position", glm::value_ptr(obj->position), 0.1f);
                        ImGui::DragFloat3("Rotation", glm::value_ptr(obj->rotation), 0.1f);
                        ImGui::DragFloat3("Scale",    glm::value_ptr(obj->scale),    0.1f);
                        ImGui::ColorEdit4("Color",    glm::value_ptr(obj->objectColor.color));
                        ImGui::TreePop();
                    }
                }
            }

            ImGui::End();
        }

        void startLoop(Render* r) override
        {
            render = r;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

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