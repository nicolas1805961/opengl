#version 440

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 grass_direction;
layout (location = 3) in float grass_height;

out vec3 normal;
out vec3 direction;
out float height;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); 
    normal = normalize(aNormal);
    direction = grass_direction;
    height = grass_height;
}