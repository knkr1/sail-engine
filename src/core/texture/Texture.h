#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include "engine/shader/Shader.h"

struct TextureProfile
{
    unsigned int wrap = GL_MIRRORED_REPEAT;
    
    unsigned int minFilter = GL_LINEAR_MIPMAP_LINEAR;

    unsigned int magFilter = GL_LINEAR;

    void bind(){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }
};

class Texture
{
    unsigned int textureID;
    unsigned int slot;
    TextureProfile profile;
    public:
        Texture(std::string path, const TextureProfile& profile = TextureProfile(),unsigned int slot = 0) : profile(profile), slot(slot)
        {
            std::cout << "[TEXTURE] Loading: " << path << std::endl;
            
            glGenTextures(1, &textureID);  
            glBindTexture(GL_TEXTURE_2D, textureID); 
            this->profile.bind();

            int width, height, nrChannels;
            //Well, you're technically calling it each time loading a texture. Not good.
            stbi_set_flip_vertically_on_load(true);
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

            //Check Format
            GLenum format;
            if (nrChannels == 1) format = GL_RED;
            else if (nrChannels == 3) format = GL_RGB;
            else if (nrChannels == 4) format = GL_RGBA;

            if(data)
            {
                std::cout << "[TEXTURE] Loaded " << path << " (" << width << "x" << height << ", " << nrChannels << " channels)" << std::endl;
                //fix for corrupted images
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "[TEXTURE] ✗ FAILED to load: " << path << std::endl;
            }
            stbi_image_free(data);

        }
        void bind()
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D,textureID);
        }
    private:

};