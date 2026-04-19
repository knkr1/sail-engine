#pragma once

#include "mesh.h"
#include <unordered_map>
#include <string>

class MeshLibrary
{

    public:
        static void init();
        static Mesh* get(const std::string& name);

    private:
        static std::unordered_map<std::string, Mesh> meshes;
};