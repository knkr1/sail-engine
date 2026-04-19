#pragma once

#include "game/objects/part/Part.h"
#include "game/objects/SceneObject.h"

#include "game/camera/camera.h"
#include "render/window/window.h"
#include "core/resources/mesh/MeshLibrary.h"

#include "render/imgui/ImGui.h"

#include "game/input/Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <vector>

struct ImGui_Preset1;

class Renderer{
    public:
        std::vector<SceneObject*> sceneObjects;

        Camera* camera;
        Window* window;

        SceneObject* lightObject;

        //The ImGui Preset
        ImGui_Preset1* preset;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        Renderer(Window* window, Camera* camera);

        void BeforeRender()
        {
            window->pollEvents();
            clearWindow();
        }

        void RenderLoop();

        void AfterRender()
        {
        }

        void addObject(SceneObject& object)
        {
            sceneObjects.push_back(&object);
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