#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

class Color{
    public:
        Color(float r=1,float g=1, float b = 1, float a= 1)
        {
            //long ass way to check if values are between 0 and 1 (sorry)
            if((r>1 ||r<0)||(g>1 || g<0)||(b>1 ||b<0)||(a>1 ||a<0)){
                std::cout << "Color parameters must be between 1-0 (They'll be automaticly set to 1)" << std::endl;
                r=1;g=1;b=1;a=1;
            }

            linearRed=r;linearGreen=g;linearBlue=b;linearAlpha=a;
        }
        void fromRGB(float r,float g, float b, float a = 255)
        {
            linearRed = r/255.0f;
            linearGreen = g/255.0f;
            linearBlue = b/255.0f;
            linearAlpha = a/255.0f;
        }
        std::vector<float> getValues() {
            return {linearRed,linearGreen,linearBlue,linearAlpha};
        }
        void applyToShader(Shader* shader){
            shader->setFloat4("uColor", getValues().data());
        }
    private:
        float linearRed,linearGreen,linearBlue,linearAlpha;

};