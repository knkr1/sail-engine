#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

uniform sampler2D texture1;
uniform bool useTexture;
in vec2 TexCoord;


void main()
{
    vec4 baseColor = useTexture
        ? texture(texture1, vec2(TexCoord.x, -TexCoord.y))
        : vec4(lightColor, 1.0);
    FragColor = vec4(lightColor, 1.0) * baseColor;
}