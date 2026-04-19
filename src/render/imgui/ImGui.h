#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void ImGui_Init(GLFWwindow* window);
void ImGui_Loop_Start(std::function<void()> presetFunction);
void ImGui_Loop_End();
void ImGui_Cleanup();

