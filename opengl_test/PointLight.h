#pragma once

#include "Light.h"
#include "Vector3.h"

class PointLight: public Light
{
public:
	PointLight(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
		const Vector3& position, float constant, float linear, float quadratic);
	
private:
	Vector3 m_position;
	float m_constant;
	float m_linear;
	float m_quadratic;
};
