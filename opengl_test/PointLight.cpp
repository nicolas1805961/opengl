#include "PointLight.h"

PointLight::PointLight(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
	const Vector3& position, float constant, float linear, float quadratic): 
	Light(shader, ambient, diffuse, specular, name), m_position(position), m_constant(constant), m_linear(linear), m_quadratic(quadratic)
{
	m_shader.set_uniform_3f(name + ".ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
	m_shader.set_uniform_3f(name + ".diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
	m_shader.set_uniform_3f(name + ".specular", m_specular[0], m_specular[1], m_specular[2]);
	m_shader.set_uniform_3f(name + ".position", m_position[0], m_position[1], m_position[2]);
	m_shader.set_uniform_1f(name + ".constant", m_constant);
	m_shader.set_uniform_1f(name + ".linear", m_linear);
	m_shader.set_uniform_1f(name + ".quadratic", m_quadratic);
	//test_opengl_error(0);
}
