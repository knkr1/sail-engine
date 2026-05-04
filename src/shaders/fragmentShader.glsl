#version 330 core

uniform sampler2D texture1;
uniform vec4 objectColor;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(texture1, TexCoord) * objectColor;
}