#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in vec3 color;
layout(location = 3) in float size;

out vec3 Color;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Color = color;
	gl_Position = /*projection * view **/ projection * view * vec4(position, 1.0f);
	gl_PointSize = size;
}