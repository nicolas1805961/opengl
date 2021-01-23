#version 440

out vec4 FragColor;

in vec3 Color;

void main() 
{
	vec2 coord = gl_PointCoord * 2 - 1;
	if(length(coord) > 1)
		discard;
	else
		FragColor = vec4(Color, 0.15);
}