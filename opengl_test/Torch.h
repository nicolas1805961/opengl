#pragma once

#include "Vector3.h"
#include "Shader.h"
#include "Light.h"

class Torch: public Light
{
public:
	Torch(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
		const Vector3& position, const Vector3& direction, float nearBorder, float farBorder, float constant, float linear, float quadratic);
	
private:
	Vector3 m_translation;
	Vector3 m_direction;
	float m_nearBorder;
	float m_farBorder;
	float m_constant;
	float m_linear;
	float m_quadratic;
};