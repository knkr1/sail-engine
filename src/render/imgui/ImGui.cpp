#include "ImGui.h" 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

void ImGui_Init(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;   // We want to handle cursor ourselves via camera.h
    //TODO: ADD DOCKING FEATURE

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

void ImGui_Loop_Start(std::function<void()> presetFunction=[](){ ImGui::ShowDemoWindow(); })
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    presetFunction();
}

void ImGui_Loop_End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ImGui_Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool ImGui_WantCaptureMouse()
{
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse;
}