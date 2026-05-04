#pragma once

#include <glad/glad.h>

#include "../Object.h"

class Block : public Object
{
    public:
        Block(Mesh* mesh, Texture* texture, Shader* shader, const Color& color = Color::fromRGB(200,200,200))
        {

            this->mesh = mesh;
            this->texture = texture;
            this->objectColor = color;
            this->shader = shader;

            this->position = glm::vec3(0.0f);
            this->rotation = glm::vec3(0.0f);
            this->scale = glm::vec3(1.0f);
        }
        void draw() override
        {
            mesh->bind();
            glDrawArrays(GL_TRIANGLES,0,mesh->vertexCount);
        }
        void updateModelMatrix() override
        {
            model = glm::mat4(1.0f);
            model=glm::translate(model,position);

            model=glm::rotate(model,rotation.x,glm::vec3(0,1,0));
            model=glm::rotate(model,rotation.y,glm::vec3(1,0,0));
            model=glm::rotate(model,rotation.z,glm::vec3(0,0,1));

            model=glm::scale(model,scale);
        }
        

    private:

};