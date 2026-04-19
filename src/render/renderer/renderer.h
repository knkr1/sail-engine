#pragma once

#include "game/part/Part.h"
#include "game/camera/camera.h"
#include "render/window/window.h"
#include "core/resources/mesh/MeshLibrary.h"

#include "render/imgui/ImGui.h"
#include "render/imgui/presets/ImGui_Preset1.h"

#include "game/input/Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <vector>

class Renderer{
    public:
        std::vector<Part*> parts;

        Camera* camera;
        Window* window;

        //The ImGui Preset
        ImGui_Preset1 preset = ImGui_Preset1(&parts);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        Renderer(Window* window, Camera* camera) : camera(camera), window(window) {
            MeshLibrary::init();
            ImGui_Init(window->windowElement);
        }

        void BeforeRender()
        {
            window->pollEvents();
            clearWindow();
        }

        void RenderLoop()
        {
            //Process Input
            Input::processInput(window->windowElement);

            //ImGui Start of the Loop
            ImGui_Loop_Start([this](){ preset.renderPreset(); });
            
            //Delta time
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            camera->CameraInputLoop(window->windowElement,deltaTime);


            //Render
            for(int i = 0;i<parts.size();i++)
            {
                //Load Model
                Part* currentPart = parts.at(i);
                
                //Update model matrix
                currentPart->updateModel();
                //Use shader -> Apply Texture -> Apply Color
                currentPart->material->use();
                //Send model matrix to shader
                currentPart->applyModelMatrix();


                //Send view and projection matrices to shader
                currentPart->material->getShader()->setMat4("view", camera->GetViewMatrix());
                currentPart->material->getShader()->setMat4("projection", glm::perspective(glm::radians(camera->Zoom), (float)window->width / (float)window->height, 0.1f, 100.0f));

                //Bind cube buffer
                currentPart->mesh->bind();
                //Draw
                glDrawArrays(GL_TRIANGLES,0,currentPart->mesh->indexCount);
            }

            //ImGui End of the Loop
            ImGui_Loop_End();
        }

        void AfterRender()
        {
        }

        void addPart(Part* part)
        {
            parts.push_back(part);
        }

        void clearWindow()
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void RenderCleanup()
        {
            ImGui_Cleanup();
        }
    private:
};