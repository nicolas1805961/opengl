#pragma once

#include "Light.h"
#include "Vector3.h"

class DirectionalLight: public Light
{
public:
	DirectionalLight(Shader const& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
		const Vector3& direction);
	
private:
	Vector3 m_direction;
};