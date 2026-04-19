#pragma once

#include "../ImGui.h"

#include "game/objects/part/Part.h"
#include "game/objects/SceneObject.h"

#include <vector>

class Renderer;

struct ImGui_Preset1
{
    std::vector<SceneObject*>* sceneObjects;
    Renderer* renderer;

    ImGui_Preset1(std::vector<SceneObject*>* sceneObjects, Renderer* renderer) : sceneObjects(sceneObjects), renderer(renderer) {}
    void renderPreset();
};