#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

uniform sampler2D texture1;
in vec2 TexCoord;


void main()
{
    FragColor = vec4(lightColor, 1.0) * texture(texture1, TexCoord);
}