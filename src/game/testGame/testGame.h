#pragma once

#include "../Game.h"

#include "engine/Render.h"
#include "core/mesh/Shapes.h"

#include "core/object/block/block.h"
#include "core/event/Event.h"

class testGame : public Game
{
    public:
        Texture* texture;
        Shader* shader;
        Render* render;

        Event<> toggleMouseCapture; 

        Block* part1;

        Shader* sunShader;
        Block* sun;

        void onStart(Render* renderObject) override {
            render = renderObject;
            texture = new Texture("assets/deima.png");
            shader = new Shader("shaders/vertexShader.glsl","shaders/fragmentShader.glsl");
            part1 = new Block(Shapes::cube, texture, shader);

            part1->position = glm::vec3(0, 0, -3);
            objectArray.push_back(part1);

            //Sun
            sunShader = new Shader("shaders/vertexShader.glsl","shaders/lightFragmentShader.glsl");

            sun = new Block(Shapes::cube,nullptr,sunShader);
            sun->objectColor = Color::fromRGB(255,255,255);
            sun->position = glm::vec3(0, 2, -4);
            sun->scale = glm::vec3(0.3f);
            renderObject->sun = sun;
            objectArray.push_back(sun);
        }

        void onUpdate() override {
            part1->rotation.x += render->deltaTime;
            part1->rotation.y += render->deltaTime;
        }

        //input poll: Checked every frame, good for movement, etc.
        void input_poll(GLFWwindow* w) override
        {

            if(glfwGetKey(w,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
                render->camera.cameraSpeed = 2;
            if(glfwGetKey(w,GLFW_KEY_LEFT_SHIFT)==GLFW_RELEASE)
                render->camera.cameraSpeed = 1;

        }
        //input callback: uses glfwCallback, good for single press purposes
        void input_callback(GLFWwindow* w, int key, int scancode, int action, int mods) override
        {
    
            if(key == GLFW_KEY_X && action == GLFW_PRESS) { 
                render->camera.isCaptured = !render->camera.isCaptured;
                render->camera.firstCapture = true;
                render->window.toggleCaptureMouse();
            }
            if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { 
                glfwSetWindowShouldClose(w, true);
            }
             if(key == GLFW_KEY_F11 && action == GLFW_PRESS) { 
                if(render->window.currentWindowMode == MINIMIZED || render->window.currentWindowMode == MAXIMIZED)
                {
                    render->window.windowModeBeforeFullscreen == render->window.currentWindowMode;
                    render->window.setWindowMode(FULLSCREEN);
                }
                else{
                    render->window.setWindowMode(render->window.windowModeBeforeFullscreen);
                }
            }
        }
    private:
};