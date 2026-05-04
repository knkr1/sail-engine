#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Color
{
    glm::vec4 color;

    Color() : color(1.0f, 1.0f, 1.0f, 1.0f) {}  // default white
    Color(float a, float b, float c, float d)
    {
        color = glm::vec4(a,b,c,d);
    }

    static Color fromRGB(uint16_t  R, uint16_t  G, uint16_t  B)
    {
        return Color(R/255.0f,G/255.0f,B/255.0f,1.0f);
    }
};