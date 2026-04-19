#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

struct Color{

    float colorData[4] = {1,1,1,1};
    Color(float r=1,float g=1, float b = 1, float a= 1)
    {
        //long ass way to check if values are between 0 and 1 (sorry)
        if((r>1 ||r<0)||(g>1 || g<0)||(b>1 ||b<0)||(a>1 ||a<0)){
            std::cout << "Color parameters must be between 1-0 (They'll be automaticly set to 1)" << std::endl;
            r=1;g=1;b=1;a=1;
        }

        colorData[0] = r; colorData[1] = g; colorData[2] = b; colorData[3] = a;
    }
    void fromRGB(float r,float g, float b, float a = 255)
    {
        colorData[0] = r/255.0f;
        colorData[1] = g/255.0f;
        colorData[2] = b/255.0f;
        colorData[3] = a/255.0f;
    }
    float* getValues() {
        return colorData;
    }
    void applyToShader(Shader* shader){
        shader->setFloat4("uColor", colorData);
    }

};