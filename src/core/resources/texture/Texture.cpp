#include "Texture.h"

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "libraries/stb_image.h"
#include "libraries/sailUtil.h"
#include <filesystem>

#define LOG(x) std::cout << x << std::endl;

namespace fs = std::filesystem;

Texture::Texture(const char* path, unsigned int textureSlot) : slot(textureSlot), directory((unsigned char*)path)
{
    isTextureGif = false;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Fixes skewed images
        glTexImage2D(GL_TEXTURE_2D, 0, getFormat(nrChannels), width, height, 0, getFormat(nrChannels), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D,0);
}

Texture::Texture(const char* path, unsigned int textureSlot, float frameDelay) : slot(textureSlot), directory((unsigned char*)path), frameDelay(frameDelay)
{
    isTextureGif = true;
    glGenTextures(1,&textureID);
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
            frameCount++;
    }
    frameCount--; //Frames start from 0
    frameCount=104;
    LOG("Frame count:"<<frameCount);
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
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Fixes skewed images
        glTexImage2D(GL_TEXTURE_2D, 0, getFormat(nrChannels), width, height, 0, getFormat(nrChannels), GL_UNSIGNED_BYTE, data);
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
    if(isTextureGif)
    {
        std::string framePath = std::string((char*)directory) + "/" + "frame_" + sailUtil::repeatString("0", 3 - std::to_string(currentFrame).length()) + std::to_string(currentFrame) + "_delay-0.1s" + ".png";
        LOG("Loading frame: " + framePath);
        glBindTexture(GL_TEXTURE_2D,textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        data = stbi_load(framePath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Fixes skewed images
            glTexImage2D(GL_TEXTURE_2D, 0, getFormat(nrChannels), width, height, 0, getFormat(nrChannels), GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        //stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D,0);
    }
    if(!isCustomSlot)
    {
        customSlot = slot;
    }
    glActiveTexture(GL_TEXTURE0+customSlot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::incrementFrame()
{
    currentFrame++;
    if(currentFrame > frameCount) 
    {
        currentFrame = 0;
    }
}

GLenum Texture::getFormat(int& channels)
{
    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;
    else
        format = GL_RGB; // fallback
    return format;
}