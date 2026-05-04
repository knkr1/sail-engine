#pragma once

#include <vector>

#include "engine/window/Window.h"
#include "core/object/Object.h"
#include "core/camera/Camera.h"
#include "libraries/sailUtil.h"

#include "game/Game.h"

#include "engine/ui/UI.h"
#include "engine/ui/presets/demoUI.h"

//Temporary for Lighting Chapter

class Render
{
    public:

        Window& window;
        Camera camera;
    
        Game* game;
        UI* ui = nullptr;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;


        //Temporary for lighting chapter
        Object* sun;

        //Game values(?)

        float ambientStrength = 0.1;
        Color gameColor = Color::fromRGB(51, 77, 77);
        Color worldLightColor = Color::fromRGB(255,255,255);

        //TEMPORARY
        glm::mat4 projection;


        Render(Window& window, Game& game) : window(window), game(&game)
        {
            camera = Camera();
        }

        void RenderObject(Object* obj)
        {
            obj->shader->bind();    
    
            // Texture defaults
            obj->shader->setBool("hasTexture", false);
            obj->shader->setInt("texture1", 0);

            // Light defaults
            obj->shader->setBool("hasLight", false);
            obj->shader->setFloat("lightColor", glm::vec3(1.0f));
            obj->shader->setFloat("lightPosition", glm::vec3(0.0f));

            // Matrices
            obj->updateModelMatrix();
            obj->shader->setMat4("model", obj->model);
            obj->shader->setMat4("view", camera.getViewMatrix());
            obj->shader->setMat4("projection", projection);

            //Color
            obj->shader->setFloat("color", obj->objectColor.color);

            //Ambient
            obj->shader->setFloat("ambientStrength", ambientStrength);
            obj->shader->setFloat("worldLightColor", glm::vec3(worldLightColor.color));

            // Override with actual values
            if(obj->texture != nullptr)
            {
                obj->texture->bind();
                obj->shader->setBool("hasTexture", true);
            }

            if(sun != nullptr)
            {
                obj->shader->setBool("hasLight", true);
                obj->shader->setFloat("lightColor", glm::vec3(sun->objectColor.color));
                obj->shader->setFloat("lightPosition", sun->position);
            }

            obj->draw();
        }

        void RenderLoop()
        {
            LOG("=== RENDER LOOP STARTED ===");
            if(ui==nullptr)
            {
                LOG("WARNING::RENDER::UI IS NULLPTR")
            }
    
            game->onStart(this);
            window.input_callback = [this](GLFWwindow* w, int key, int scancode, int action, int mods) {
                game->input_callback(w,key,scancode,action,mods);
            };

            window.toggleCaptureMouse();
            window.mouse_callback = [this](GLFWwindow* win, double x, double y){
                camera.processMouse(win,x,y);
            };
            //for future errors
            if(game->objectArray.size()<1)
            {
                LOG("WARNING::RENDER::NO OBJECT IN OBJECT ARRAY!");
            }
            while (!glfwWindowShouldClose(window.windowObject))
            {  

                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;  

                game->onUpdate();

                Color tempGameColor = gameColor;
                tempGameColor.color *= glm::vec4(worldLightColor.color.x,worldLightColor.color.y,worldLightColor.color.z,1.0f);
                glClearColor(tempGameColor.color.x,tempGameColor.color.y,tempGameColor.color.z,tempGameColor.color.w);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


                projection = camera.getProjectionMatrix(window);
                for(int i=0;i<game->objectArray.size();i++)
                {
                    RenderObject(game->objectArray.at(i));
                }

                if(ui)ui->startLoop(this);
                if(ui)ui->endLoop();
    
                glfwSwapBuffers(window.windowObject);

                glfwPollEvents();

                game->input_poll(window.windowObject);

                camera.processKeyboard(window.windowObject, deltaTime);
            }
            LOG("=== RENDER LOOP ENDED ===");
            if(ui)ui->terminate();
        }

        void bindUI(UI& uiToBind)
        {
            ui = &uiToBind;
        }

    private:

};