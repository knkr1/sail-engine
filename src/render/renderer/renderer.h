#pragma once

#include "game/part/Part.h"
#include "game/camera/camera.h"
#include "render/window/window.h"
#include "core/resources/mesh/MeshLibrary.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <vector>

class Renderer{
    public:
        std::vector<Part*> parts;

        Camera* camera;
        Window* window;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        Renderer(Window* window, Camera* camera) : camera(camera), window(window) {
             MeshLibrary::init();
        }

        void RenderLoop()
        {
            //Delta time
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            camera->CameraInputLoop(window->windowElement,deltaTime);


            for(int i = 0;i<parts.size();i++)
            {
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
    private:
};