#pragma once

#include "core/resources/mesh/MeshLibrary.h"
#include "core/resources/material/Material.h"

#include <glm/glm.hpp>          
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

struct Part
{
    Mesh* mesh;
    Material* material;

    glm::vec3 scale;
    glm::vec3 position;
    glm::vec3 rotation;

    glm::mat4 model;
    Part(Material& mat)
    {
        mesh = MeshLibrary::get("cube");
        material = &mat;
        scale = glm::vec3(1,1,1);
        position = glm::vec3(0,0,0);
        rotation = glm::vec3(0,0,0);
        updateModel();
    };
    void applyModelMatrix()
    {
        Shader* currentShader = material->getShader();
        currentShader->setMat4("model",model);

    }
    void updateModel()
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, position);

        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(1,0,0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0,0,1));

        model = glm::scale(model, scale);

    }
    void setPosition(float x,float y,float z)
    {
        position = glm::vec3(x,y,z);
    }
    void setScale(float x,float y,float z)
    {
        scale = glm::vec3(x,y,z);
    }
    void setRotation(float x,float y,float z)
    {
        rotation = glm::vec3(x,y,z);
    }

};