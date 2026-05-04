#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "libraries/stb_image.h"

struct Texture
{

    bool isTextureGif;

    int currentFrame;
    int frameCount;
    float frameDelay;

    unsigned char* data;
    int width, height, nrChannels;
    unsigned char* directory;

    unsigned int textureID;
    unsigned int slot;

    Texture(const char* path, unsigned int textureSlot);
    Texture(const char* path, unsigned int textureSlot, float frameDelay);
    void incrementFrame();
    void use(bool isCustomSlot = false, int customSlot = 0);
    void ChangeTexture(const char* path, unsigned int textureSlot);
    GLenum getFormat(int& channels);
};