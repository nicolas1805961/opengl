#pragma once

#include "Vector3.h"
#include "Shader.h"
#include "Light.h"

class SpotLight: public Light
{
public:
	SpotLight(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
		const Vector3& position, const Vector3& direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic);
	
private:
	Vector3 m_translation;
	Vector3 m_direction;
	float m_cutOff;
	float m_outerCuttOff;
	float m_constant;
	float m_linear;
	float m_quadratic;
};