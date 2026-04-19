#include "renderer.h"
#include "render/imgui/presets/ImGui_Preset1.h"
#include "game/input/Input.h"
#include <GLFW/glfw3.h>
#include <cassert>

Renderer::Renderer(Window* window, Camera* camera) : camera(camera), window(window) {
    MeshLibrary::init();
    ImGui_Init(window->windowElement);
    preset = new ImGui_Preset1(&sceneObjects, this);
}

void Renderer::RenderLoop()
{
    //Process Input
    Input::processInput(window->windowElement);

    //ImGui Start of the Loop
    ImGui_Loop_Start([this](){ preset->renderPreset(); });
    
    //Delta time
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    camera->CameraInputLoop(window->windowElement,deltaTime);


    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)window->width / (float)window->height, 0.1f, 100.0f);
    
    //Calculate Light Data
    //TODO: READ ALL OBJECTS TO GET LIGHT ONES
    LightData lightData;
    if(lightObject != nullptr){
        lightData.positions.push_back(lightObject->position);
        lightData.colors.push_back(lightObject->getMaterial()->materialColor.colorData);
    }
    else{
        assert(false && "No light object set in the renderer.");
    }
    
    float currentTime = glfwGetTime();

    //Render
    //lightObject->position[0] = 2.0f * sin(currentTime);
    lightObject->render(view, projection, camera, lightData);
    for(SceneObject* obj : sceneObjects)
    {
        obj->render(view, projection, camera, lightData);
    }

    //ImGui End of the Loop
    ImGui_Loop_End();
}
