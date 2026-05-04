#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 UV;
in vec3 FragPosition;

uniform bool hasTexture;
uniform sampler2D texture1;
uniform vec4 color;

void main()
{
    if(hasTexture)
    {
        FragColor = texture(texture1,UV) * color;
    } else{
        FragColor = color;
    }
}