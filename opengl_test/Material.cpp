#include "Material.h"

Material::Material(const Shader& shader, float shininess, std::string const& name): m_shader(shader), m_shininess(shininess), m_name(name)
{
	m_shader.bind();
	m_shader.set_uniform_1i(name + ".diffuse", 0);
	m_shader.set_uniform_1i(name + ".specular", 1);
	m_shader.set_uniform_1f(name + ".shininess", m_shininess);
}

Material::Material(const Shader& shader, float shininess, std::string const& name, Vector3 const& diffuse, Vector3 const& specular) :
	m_shader(shader), m_shininess(shininess), m_name(name), m_diffuse(diffuse), m_specular(specular)
{
	m_shader.bind();
	m_shader.set_uniform_3f(name + ".diffuse", m_diffuse.get_x(), m_diffuse.get_y(), m_diffuse.get_z());
	m_shader.set_uniform_3f(name + ".specular", m_specular.get_x(), m_specular.get_y(), m_specular.get_z());
	m_shader.set_uniform_1f(name + ".shininess", m_shininess);
}
