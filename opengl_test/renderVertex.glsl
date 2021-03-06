#version 440
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoordinates;

out vec2 texCoord;

void main()
{
	texCoord = textureCoordinates;
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}