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
private:
};