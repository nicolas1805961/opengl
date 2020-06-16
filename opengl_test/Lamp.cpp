#include "Lamp.h"

Lamp::Lamp(Shader const& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
	std::shared_ptr<Object> const& shape): Light(shader, ambient, diffuse, specular, name), m_shape(shape)
{
	m_shader.bind();
	m_shader.set_uniform_3f(name + ".position", m_shape->getTranslation()[0], m_shape->getTranslation()[1], m_shape->getTranslation()[2]);
	m_shader.set_uniform_3f(name + ".lightProperty.ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
	m_shader.set_uniform_3f(name + ".lightProperty.diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
	m_shader.set_uniform_3f(name + ".lightProperty.specular", m_specular[0], m_specular[1], m_specular[2]);
}

std::shared_ptr<Object> Lamp::getShape()
{
	return m_shape;
}
