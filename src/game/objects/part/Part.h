#pragma once

#include "game/objects/SceneObject.h"

#include "core/resources/mesh/MeshLibrary.h"
#include "core/resources/material/Material.h"

#include "game/camera/Camera.h"

#include <glm/glm.hpp>          
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

struct Part : public SceneObject
{
    Mesh* mesh;
    Material* material;

    glm::mat4 model;
    Part(Material& mat) : material(&mat)
    {
        mesh = MeshLibrary::get("cube");
        scale = glm::vec3(1);
        position = glm::vec3(0);
        rotation = glm::vec3(0);
        updateModel();
    };
    void render(glm::mat4& view, glm::mat4& projection, Camera* camera) override
    {
        //Update model matrix
        updateModel();
        //Use shader -> Apply Texture -> Apply Color
        material->use();
        //Send model matrix to shader
        applyModelMatrix();

        //Send view and projection matrices to shader
        material->getShader()->setMat4("view", view);
        material->getShader()->setMat4("projection", projection);

        if(material->materialTexture != nullptr){
            material->getShader()->setBool("useTexture", true);
        }
        else{
            material->getShader()->setBool("useTexture", false);
        }

        float viewPos[3] = {camera->Position.x, camera->Position.y, camera->Position.z};
        material->getShader()->setVec3("viewPos", viewPos);

        //Bind cube buffer
        mesh->bind();
        //Draw
        glDrawArrays(GL_TRIANGLES,0,mesh->indexCount);
    }

    void applyModelMatrix()
    {
        material->getShader()->setMat4("model",model);

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
    Material* getMaterial() override
    {
        return material;
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