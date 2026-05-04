#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 color;

//Lighting stuff
uniform bool hasLight;
uniform vec3 lightColor;

uniform float ambientStrength;
uniform vec3 worldLightColor;

void main()
{
    vec3 ambient = ambientStrength * worldLightColor;
    if(hasLight)
    {
        ambient *= lightColor;
    }
    vec4 result = vec4(ambient,1.0) * color;
    FragColor = texture(texture1,TexCoord) * result;
}