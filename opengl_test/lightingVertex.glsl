#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 Normal;
out vec3 vertexPosition;
out vec4 positionToLight;
out vec3 color;
//out float visibility;

//uniform float density;
//uniform float gradient;
uniform mat4 shadowView;
uniform mat4 shadowProjection;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	color = vec3(1,0,0);
	//vec4 positionToCamera = view * model * vec4(position, 1.0f);
	//float distanceToCamera = -positionToCamera.z;
	vertexPosition = vec3(model * vec4(position, 1.0f));
	gl_Position = projection * view * vec4(vertexPosition, 1.0f);
	Normal = mat3(transpose(inverse(model))) * normal;
	positionToLight = shadowProjection * shadowView * vec4(vertexPosition, 1.0f);
	//visibility = clamp(exp(-pow(distanceToCamera * density, gradient)), 0.0, 1.0);
}