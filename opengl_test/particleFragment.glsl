#version 440

out vec4 FragColor;

in vec3 Color;
in float Lifespan;
in float Size;

void main() 
{
	FragColor = vec4(Color, 1.0);
}