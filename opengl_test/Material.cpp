#include "Material.h"

Material::Material(const Shader& shader, float shininess, std::string const& name): m_shader(shader), m_shininess(shininess), m_name(name)
{
	m_shader.set_uniform_1i(name + ".diffuse", 0);
	m_shader.set_uniform_1i(name + ".specular", 1);
	m_shader.set_uniform_1f(name + ".shininess", m_shininess);
	//test_opengl_error(0);
}
