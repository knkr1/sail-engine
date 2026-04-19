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

    //For Lighting
    std::string label = "Lighting 1";
        
    if(ImGui::CollapsingHeader(label.c_str()))
    {
        ImGui::PushID(99); // prevent widget ID conflicts between parts
        
        ImGui::SliderFloat("Pos X", &renderer->lightObject->position.x, -10.0f, 10.0f);
        ImGui::SliderFloat("Pos Y", &renderer->lightObject->position.y, -10.0f, 10.0f);
        ImGui::SliderFloat("Pos Z", &renderer->lightObject->position.z, -10.0f, 10.0f);
        
        ImGui::SliderFloat("Rot X", &renderer->lightObject->rotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat("Rot Y", &renderer->lightObject->rotation.y, -180.0f, 180.0f);
        ImGui::SliderFloat("Rot Z", &renderer->lightObject->rotation.z, -180.0f, 180.0f);
        
        ImGui::SliderFloat("Scale X", &renderer->lightObject->scale.x, 0.0f, 10.0f);
        ImGui::SliderFloat("Scale Y", &renderer->lightObject->scale.y, 0.0f, 10.0f);
        ImGui::SliderFloat("Scale Z", &renderer->lightObject->scale.z, 0.0f, 10.0f);
        
        ImGui::ColorEdit4("Color", 
            &renderer->lightObject->getMaterial()->materialColor.colorData[0]);


        static char vertexPath[256] = "shaders/lightingVertexShader.glsl";
        ImGui::InputText("Vertex Shader Path", vertexPath, 256);
        static char fragmentPath[256] = "shaders/lightingFragmentShader.glsl";
        ImGui::InputText("Fragment Shader Path", fragmentPath, 256);
        if(ImGui::Button("Update Shaders")){
            renderer->lightObject->getMaterial()->materialShader->UpdateShader(vertexPath, fragmentPath);
        }
        
        ImGui::PopID();
    }

    ImGui::End();
}