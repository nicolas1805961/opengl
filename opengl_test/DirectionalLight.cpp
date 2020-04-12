#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Shader const& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular,
    std::string const& name, const Vector3& direction, bool night): Light(shader, ambient, diffuse, specular, name, night), m_direction(direction)
{
	m_shader.bind();
	m_shader.set_uniform_3f(name + ".direction", m_direction[0], m_direction[1], m_direction[2]);
	if (!night)
	{
		m_shader.set_uniform_3f(name + ".ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
		m_shader.set_uniform_3f(name + ".diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
		m_shader.set_uniform_3f(name + ".specular", m_specular[0], m_specular[1], m_specular[2]);
	}
	else
	{
		m_shader.set_uniform_3f(name + ".ambient", 0.02f, 0.02f, 0.02f);
		m_shader.set_uniform_3f(name + ".diffuse", 0.02f, 0.02f, 0.02f);
		m_shader.set_uniform_3f(name + ".specular", 0.02f, 0.02f, 0.02f);
	}
}
