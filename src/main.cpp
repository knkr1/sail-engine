#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "engine/Render.h"
#include "core/mesh/Shapes.h"

#include "core/object/block/block.h"

#include "game/testGame/testGame.h"
#include "engine/ui/presets/demoUI.h"
#include "engine/ui/presets/testUI.h"

int main()
{
    LOG("=== ENGINE STARTUP ===");

    Window window("SailEngine",800,600);

    
    //WARNING: Shapes use glad functions, and glad functions initialized inside of the window class.
    Shapes::init();

    testGame myGame;
    Render render(window, myGame);

    testUI myUI(&window);
    render.bindUI(myUI);



    
    render.RenderLoop();

    LOG("Terminating window...");
    window.terminate();
    LOG("=== ENGINE SHUTDOWN ===");
    return 0;
}