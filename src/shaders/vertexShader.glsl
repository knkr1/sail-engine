#version 330 core

layout (location=0) in vec3 aPosition;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aUV;

out vec3 Normal;
out vec2 UV;

out vec3 FragPosition;

uniform mat4 model, view, projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition,1.0);
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    FragPosition = vec3(model * vec4(aPosition, 1.0));
    UV = aUV;
}