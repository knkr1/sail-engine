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

        Material(Shader* shader, Texture* texture = nullptr)
        {
            materialShader = shader;
            materialColor = Color();
            materialTexture = texture;
        }
        void use()
        {
            materialShader->use();
            materialColor.applyToShader(materialShader);
            
            if(materialTexture != nullptr)
                materialTexture->use();
        }
        Shader* getShader() 
        {
            return materialShader;
        }
    private:

};