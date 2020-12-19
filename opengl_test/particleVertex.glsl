#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in vec3 color;
layout(location = 3) in float lifespan;
layout(location = 4) in float size;

out vec3 Color;
out float Size;
out float Lifespan;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	/*mat4 model = mat4(10, 0, 0, 0,
					0, 10, 0, 0,
					0, 0, 10, 0,
					0, 0, 0, 1);*/
	Lifespan = lifespan;
	Size = size;
	Color = color;
	gl_Position = /*projection * view **/ projection * view * vec4(position, 1.0f);
	gl_PointSize = size;
}