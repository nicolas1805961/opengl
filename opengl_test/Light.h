#pragma once

#include "Shader.h"
#include "Vector3.h"
#include <string>
#include "Error.h"

class Light
{
public:
	Light(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name);

protected:
	std::string m_name;
	Shader m_shader;
	Vector3 m_ambient;
	Vector3 m_diffuse;
	Vector3 m_specular;
};