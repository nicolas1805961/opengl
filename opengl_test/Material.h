#pragma once

#include "Shader.h"
#include <string>
#include "Error.h"

class Material
{
public:
	Material(const Shader& shader, float shininess, std::string const& name);

private:
	float m_shininess;
	Shader m_shader;
	std::string m_name;
};