#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "libraries/stb_image.h"

class Texture
{
    public:
        Texture(const char* path, unsigned int textureSlot);
        void use(bool isCustomSlot = false, int customSlot = 0);

    private:
        unsigned int textureID;
        unsigned int slot;
};