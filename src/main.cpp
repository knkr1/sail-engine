#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "render/window/window.h"
#include "render/shader/shader.h"
#include "render/renderer/renderer.h"

#include "game/part/Part.h"
#include "game/camera/Camera.h"

#include "core/resources/texture/Texture.h"
#include "core/resources/material/Material.h"

int main(){
    
    Window window(1280, 720, "Sail Engine", true);
    Camera camera;
    
    //Setup callbacks after ImGui_Init to prevent blocking of ImGui
    window.setupCallbacks(&camera);

    Renderer renderer(&window, &camera);

    Shader shaderProgram1("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Texture texture1("assets/bjt.jpg", 0);
    Material material1(shaderProgram1,texture1);

    Part part1(material1);
    part1.setPosition(0,0,-3);

    Shader shaderProgram2("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Texture texture2("assets/bjt.jpg", 0);
    Material material2(shaderProgram2,texture2);

    Part part2(material2);
    part2.setPosition(-1.5,0,-3);

    Shader shaderProgram3("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Texture texture3("assets/bjt.jpg", 0);
    Material material3(shaderProgram3,texture3);

    Part part3(material3);
    part3.setPosition(1.5,0,-3);

    renderer.addPart(&part1);
    renderer.addPart(&part2);
    renderer.addPart(&part3);
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
