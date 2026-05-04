#pragma once

#include <vector>

#include "engine/window/Window.h"
#include "core/object/Object.h"
#include "core/camera/Camera.h"
#include "libraries/sailUtil.h"

#include "game/Game.h"

#include "engine/ui/UI.h"
#include "engine/ui/presets/demoUI.h"

class Render
{
    public:

        Window& window;
        Camera camera;
    
        Game* game;
        UI* ui = nullptr;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        //Game values(?)

        float ambientStrength = 0.1;
        glm::vec3 worldLightColor = glm::vec3(1.0f);

        //TEMPORARY
        glm::mat4 projection;


        Render(Window& window, Game& game) : window(window), game(&game)
        {
            camera = Camera();
        }

        void RenderObject(Object* obj)
        {
            obj->shader->bind();    
            obj->updateModelMatrix();
            obj->shader->setMat4("model",obj->model);
            obj->shader->setMat4("view",camera.getViewMatrix());
            
            obj->shader->setMat4("projection",projection);

            obj->texture->bind();
            obj->shader->setInt("texture1",0);

            //Light stuff
            obj->shader->setFloat("color",glm::vec4(1.0f));
    
            obj->shader->setFloat("ambientStrength",ambientStrength);
            obj->shader->setFloat("worldLightColor",worldLightColor);
            
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

                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


                //temporarly I decided to update projection from here because it needs constant update (aspect ratio/fov)
                projection = glm::perspective(glm::radians(45.0f),(float)window.width/(float)window.height,0.1f,100.0f);
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