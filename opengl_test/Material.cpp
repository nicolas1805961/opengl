#include "Material.h"

Material::Material(const Shader& shader, float shininess, std::string const& name)
{
	shader.set_uniform_1i(name + ".diffuse", 0);
	shader.set_uniform_1i(name + ".specular", 1);
	shader.set_uniform_1f(name + ".shininess", shininess);
}

Material::Material(const Shader& shader, float shininess, std::string const& name, Vector3 const& diffuse, Vector3 const& specular)
{
	shader.set_uniform_3f(name + ".diffuse", diffuse.get_x(), diffuse.get_y(), diffuse.get_z());
	shader.set_uniform_3f(name + ".specular", specular.get_x(), specular.get_y(), specular.get_z());
	shader.set_uniform_1f(name + ".shininess", shininess);
}

