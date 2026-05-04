#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "render/window/window.h"
#include "render/shader/shader.h"
#include "render/renderer/renderer.h"

#include "game/objects/part/Part.h"
#include "game/camera/Camera.h"

#include "core/resources/texture/Texture.h"
#include "core/resources/material/Material.h"

int main(){
    
    Window window(1280, 720, "Sail Engine", false);
    Camera camera;
    
    //Setup callbacks after ImGui_Init to prevent blocking of ImGui
    window.setupCallbacks(&camera);

    Renderer renderer(&window, &camera);

    //Part 1
    Shader shaderProgram1("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Texture texture1("assets/grass.jpg",0);
    Material material1(&shaderProgram1, &texture1);
    Part part1(material1);
    part1.setPosition(0,0,-3);

    //Add Objects to the renderer
    renderer.addObject(part1);

    while(!window.shouldClose())
    {

        renderer.BeforeRender();
        renderer.RenderLoop();
        renderer.AfterRender();

        window.windowLoopEnd();
    }
    renderer.RenderCleanup();

    return 0;
}
