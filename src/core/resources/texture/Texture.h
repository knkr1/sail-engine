#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "libraries/stb_image.h"

struct Texture
{
    unsigned char* data;
    int width, height, nrChannels;
    unsigned char* directory;

    unsigned int textureID;
    unsigned int slot;

    Texture(const char* path, unsigned int textureSlot);
    void use(bool isCustomSlot = false, int customSlot = 0);
    void ChangeTexture(const char* path, unsigned int textureSlot);
};