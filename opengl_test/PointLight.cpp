#include "PointLight.h"

PointLight::PointLight(Shader const& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name, float constant,
	float linear, float quadratic, std::shared_ptr<Object> const& shape)
	: Light(shader, ambient, diffuse, specular, name), m_shape(shape), m_constant(constant), m_linear(linear), m_quadratic(quadratic)
{
	m_shader.bind();
	m_shader.set_uniform_3f(name + ".position", m_shape->getTranslation()[0], m_shape->getTranslation()[1], m_shape->getTranslation()[2]);
	m_shader.set_uniform_1f(name + ".fading.constant", m_constant);
	m_shader.set_uniform_1f(name + ".fading.linear", m_linear);
	m_shader.set_uniform_1f(name + ".fading.quadratic", m_quadratic);
	m_shader.set_uniform_3f(name + ".lightProperty.ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
	m_shader.set_uniform_3f(name + ".lightProperty.diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
	m_shader.set_uniform_3f(name + ".lightProperty.specular", m_specular[0], m_specular[1], m_specular[2]);
}

std::shared_ptr<Object> PointLight::getShape()
{
	return m_shape;
}
