#pragma once

#include "core/resources/material/Material.h"
#include "game/camera/Camera.h"

#include <glm/glm.hpp>          
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class SceneObject
{
    public:
        virtual void render(glm::mat4& view, glm::mat4& projection, Camera* camera) = 0;
        virtual Material* getMaterial() { return nullptr; }; 
    
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
};