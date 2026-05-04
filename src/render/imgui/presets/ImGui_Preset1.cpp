#include "ImGui_Preset1.h"
#include "render/renderer/renderer.h"
#include <vector>

void ImGui_Preset1::renderPreset()
{
    ImGui::Begin("Sail Engine - ImGui Preset 1");

    for(int i = 0; i < sceneObjects->size(); i++)
    {
        SceneObject* obj = sceneObjects->at(i);
        
        std::string label = "Object " + std::to_string(i);
        
        if(ImGui::CollapsingHeader(label.c_str()))
        {
            ImGui::PushID(i); // prevent widget ID conflicts between parts
            
            ImGui::SliderFloat("Pos X", &obj->position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Pos Y", &obj->position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("Pos Z", &obj->position.z, -10.0f, 10.0f);
            
            ImGui::SliderFloat("Rot X", &obj->rotation.x, -180.0f, 180.0f);
            ImGui::SliderFloat("Rot Y", &obj->rotation.y, -180.0f, 180.0f);
            ImGui::SliderFloat("Rot Z", &obj->rotation.z, -180.0f, 180.0f);
            
            ImGui::SliderFloat("Scale X", &obj->scale.x, 0.0f, 10.0f);
            ImGui::SliderFloat("Scale Y", &obj->scale.y, 0.0f, 10.0f);
            ImGui::SliderFloat("Scale Z", &obj->scale.z, 0.0f, 10.0f);
            
            ImGui::ColorEdit4("Color", 
                &obj->getMaterial()->materialColor.colorData[0]);

            
            static char texturePath[256] = "assets/image.png";
            ImGui::InputText("Texture Path", texturePath, 256);
            if(ImGui::Button("Apply Texture")){
                obj->getMaterial()->materialTexture->ChangeTexture(texturePath, obj->getMaterial()->materialTexture->slot);
            }

            static char vertexPath[256] = "shaders/vertexShader.glsl";
            ImGui::InputText("Vertex Shader Path", vertexPath, 256);
            static char fragmentPath[256] = "shaders/fragmentShader.glsl";
            ImGui::InputText("Fragment Shader Path", fragmentPath, 256);
            if(ImGui::Button("Update Shaders")){
                obj->getMaterial()->materialShader->UpdateShader(vertexPath, fragmentPath);
            }
            
            ImGui::PopID();
        }
    }

    ImGui::End();
}