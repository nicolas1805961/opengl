#pragma once

#include "Light.h"
#include "Vector3.h"
#include <memory>
#include "Object.h"

class PointLight: public Light
{
public:
	PointLight(Shader const& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name, 
		float constant, float linear, float quadratic, std::shared_ptr<Object> const& shape);
	std::shared_ptr<Object> getShape();
	
private:
	std::shared_ptr<Object> m_shape;
	float m_constant;
	float m_linear;
	float m_quadratic;
};
