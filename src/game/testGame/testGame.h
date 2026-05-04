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
        Block* part1;
        Render* render;

        Event<> toggleMouseCapture; 

        void onStart(Render* renderObject) override {
            render = renderObject;
            texture = new Texture("assets/deima.png");
            shader = new Shader("shaders/vertexShader.glsl","shaders/fragmentShader.glsl");
            part1 = new Block(Shapes::cube, texture, shader);

            part1->position = glm::vec3(0, 0, -3);
            objectArray.push_back(part1);
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
        }
    private:
};