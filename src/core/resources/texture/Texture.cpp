#include "Texture.h"

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "libraries/stb_image.h"

Texture::Texture(const char* path, unsigned int textureSlot) : slot(textureSlot), directory((unsigned char*)path)
{
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::ChangeTexture(const char* path, unsigned int textureSlot)
{
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* placeHolderData = data;
    data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        slot = textureSlot;
        directory = (unsigned char*)path;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        data = placeHolderData;
        return;
    }
    //stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::use(bool isCustomSlot, int customSlot)
{
    if(!isCustomSlot)
    {
        customSlot = slot;
    }
    glActiveTexture(GL_TEXTURE0+customSlot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}