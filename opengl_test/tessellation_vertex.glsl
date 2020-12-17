#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;

out vec3 tcs_normal;

void main()
{
    gl_Position = vec4(position, 1.0); 
    tcs_normal = normalize(aNormal);
}