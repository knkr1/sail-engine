#pragma once

#include "core/resources/color/Color.h"
#include "core/resources/texture/Texture.h"
#include "render/shader/shader.h"

class Material
{
    public:
        Shader* materialShader;
        Color materialColor;
        Texture* materialTexture;
        Material(Shader& shader, Texture& texture)
        {
            materialShader = &shader;
            materialColor = Color();
            materialTexture = &texture;
        }
        void use()
        {
            materialShader->use();
            materialTexture->use();
            materialShader->setFloat4("uColor",materialColor.getValues().data());
        }
        Shader* getShader()
        {
            return materialShader;
        }
    private:

};