#include "../ImGui.h"

#include "game/part/Part.h"
#include <vector>


struct ImGui_Preset1
{
    std::vector<Part*>* parts;

    ImGui_Preset1(std::vector<Part*>* parts) : parts(parts) {}

    void renderPreset()
    {
        ImGui::Begin("Sail Engine - ImGui Preset 1");

        for(int i = 0; i < parts->size(); i++)
        {
            Part* part = parts->at(i);
            
            std::string label = "Part " + std::to_string(i);
            
            if(ImGui::CollapsingHeader(label.c_str()))
            {
                ImGui::PushID(i); // prevent widget ID conflicts between parts
                
                ImGui::SliderFloat("Pos X", &part->position.x, -10.0f, 10.0f);
                ImGui::SliderFloat("Pos Y", &part->position.y, -10.0f, 10.0f);
                ImGui::SliderFloat("Pos Z", &part->position.z, -10.0f, 10.0f);
                
                ImGui::SliderFloat("Rot X", &part->rotation.x, -180.0f, 180.0f);
                ImGui::SliderFloat("Rot Y", &part->rotation.y, -180.0f, 180.0f);
                ImGui::SliderFloat("Rot Z", &part->rotation.z, -180.0f, 180.0f);
                
                ImGui::SliderFloat("Scale X", &part->scale.x, 0.0f, 10.0f);
                ImGui::SliderFloat("Scale Y", &part->scale.y, 0.0f, 10.0f);
                ImGui::SliderFloat("Scale Z", &part->scale.z, 0.0f, 10.0f);
                
                ImGui::ColorEdit4("Color", 
                    part->material->materialColor.colorData);

                
                static char texturePath[256] = "assets/image.png";
                ImGui::InputText("Texture Path", texturePath, 256);
                if(ImGui::Button("Apply Texture")){
                    part->material->materialTexture->ChangeTexture(texturePath, part->material->materialTexture->slot);
                }

                static char vertexPath[256] = "shaders/vertexShader.glsl";
                ImGui::InputText("Vertex Shader Path", vertexPath, 256);
                static char fragmentPath[256] = "shaders/fragmentShader.glsl";
                ImGui::InputText("Fragment Shader Path", fragmentPath, 256);
                if(ImGui::Button("Update Shaders")){
                    part->material->materialShader->UpdateShader(vertexPath, fragmentPath);
                }
                
                ImGui::PopID();
            }
        }

        ImGui::End();
    }
};