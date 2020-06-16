#pragma once

#include "Vector3.h"
#include "Shader.h"
#include "Light.h"
#include "Object.h"

class Torch: public Light
{
public:
	Torch(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
		const Vector3& direction, float nearBorder, float farBorder, std::shared_ptr<Object> const& shape);
	std::shared_ptr<Object> getShape();
	
private:
	std::shared_ptr<Object> m_shape;
	Vector3 m_translation;
	Vector3 m_direction;
	float m_nearBorder;
	float m_farBorder;
};