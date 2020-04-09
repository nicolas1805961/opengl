#pragma once

#include "Shader.h"
#include <string>
#include "Error.h"
#include "Vector3.h"

class Material
{
public:
	Material() = default;
	Material(const Shader& shader, float shininess, std::string const& name);
	Material(const Shader& shader, float shininess, std::string const& name, Vector3 const& diffuse, Vector3 const& specular);
	void setColor(Vector3 const& color);
private:
	float m_shininess;
	Shader m_shader;
	std::string m_name;
	Vector3 m_diffuse;
	Vector3 m_specular;
};