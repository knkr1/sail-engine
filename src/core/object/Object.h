#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/texture/Texture.h"
#include "core/mesh/Mesh.h"
#include "core/color/Color.h"

class Object
{
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 model;

        Color objectColor;
        Texture* texture;
        Mesh* mesh;
        Shader* shader;

        Object() {}

        virtual void draw() = 0; 
        virtual void updateModelMatrix() = 0;
};