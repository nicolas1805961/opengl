#include "PointLight.h"

PointLight::PointLight(Shader const& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name, float constant,
	float linear, float quadratic, std::shared_ptr<Object> const& shape, bool night)
	: Light(shader, ambient, diffuse, specular, name, night), m_shape(shape), m_constant(constant), m_linear(linear), m_quadratic(quadratic)
{
	m_shader.bind();
	m_shader.set_uniform_3f(name + ".position", m_shape->getTranslation()[0], m_shape->getTranslation()[1], m_shape->getTranslation()[2]);
	m_shader.set_uniform_1f(name + ".constant", m_constant);
	m_shader.set_uniform_1f(name + ".linear", m_linear);
	m_shader.set_uniform_1f(name + ".quadratic", m_quadratic);
	if (night)
	{
		m_shader.set_uniform_3f(name + ".ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
		m_shader.set_uniform_3f(name + ".diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
		m_shader.set_uniform_3f(name + ".specular", m_specular[0], m_specular[1], m_specular[2]);
	}
	else
	{
		m_shader.set_uniform_3f(name + ".ambient", 0.0f, 0.0f, 0.0f);
		m_shader.set_uniform_3f(name + ".diffuse", 0.0f, 0.0f, 0.0f);
		m_shader.set_uniform_3f(name + ".specular", 0.0f, 0.0f, 0.0f);
	}
}

std::shared_ptr<Object> PointLight::getShape()
{
	return m_shape;
}
