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
    
    float currentTime = glfwGetTime();

    for(SceneObject* obj : sceneObjects)
    {
        Texture* tex = obj->getMaterial()->materialTexture;
        if(tex->isTextureGif)
        {
            if(currentFrame - gifLastFrame > tex->frameDelay){
                gifLastFrame = currentFrame;
                tex->incrementFrame();
            }
        }
        obj->render(view, projection, camera);
    }

    //ImGui End of the Loop
    ImGui_Loop_End();
}
