#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;
//out float visibility;

//uniform float density;
//uniform float gradient;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//vec4 positionToCamera = view * model * vec4(position, 1.0f);
	//float distanceToCamera = -positionToCamera.z;
	FragPos = vec3(model * vec4(position, 1.0f));
	gl_Position = projection * view * vec4(FragPos, 1.0f);
	Normal = mat3(transpose(inverse(model))) * normal;
	//visibility = clamp(exp(-pow(distanceToCamera * density, gradient)), 0.0, 1.0);
}