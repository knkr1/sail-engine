#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 UV;
in vec3 FragPosition;

uniform bool hasTexture;
uniform sampler2D texture1;
uniform vec4 color;

//Lighting stuff
uniform bool hasLight;
uniform vec3 lightColor;
uniform vec3 lightPosition;

uniform float ambientStrength;
uniform vec3 worldLightColor;

void main()
{
    vec3 ambient = ambientStrength * worldLightColor;
    vec3 diffuse = vec3(0.0);
    if(hasLight)
    {
        vec3 norm = normalize(Normal);
        vec3 lightDirection = normalize(lightPosition - FragPosition);  
        float diffusion = max(dot(norm, lightDirection), 0.0);
        diffuse = diffusion * lightColor;
    }
    
    vec3 result = (ambient+diffuse)*vec3(color.xyz);

    if(hasTexture)
    {
        FragColor = texture(texture1,UV) * vec4(result.xyz,1 );
    } else{
        FragColor = vec4(result.xyz,1 );
    }
}