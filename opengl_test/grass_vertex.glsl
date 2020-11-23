#version 440

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 grass_direction;

out vec3 normal;
out vec3 sideway_vector;

uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = view * model * vec4(aPos, 1.0); 
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    normal = normalize(vec3(vec4(normalMatrix * aNormal, 0.0)));
    sideway_vector = grass_direction;
}