#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec4 uColor;

void main()
{
    FragColor = texture(texture1, vec2(TexCoord.x, -TexCoord.y)) * uColor;
}