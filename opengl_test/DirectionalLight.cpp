#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Shader const& shader1, Shader const& shader2, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular,
    std::string const& name, const Vector3& direction): Light(ambient, diffuse, specular, name), m_direction(direction)
{
	shader1.bind();
	shader1.set_uniform_3f(name + ".direction", m_direction[0], m_direction[1], m_direction[2]);
	shader1.set_uniform_3f(name + ".lightProperty.ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
	shader1.set_uniform_3f(name + ".lightProperty.diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
	shader1.set_uniform_3f(name + ".lightProperty.specular", m_specular[0], m_specular[1], m_specular[2]);

	shader2.bind();
	shader2.set_uniform_3f(name + ".direction", m_direction[0], m_direction[1], m_direction[2]);
	shader2.set_uniform_3f(name + ".lightProperty.ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
	shader2.set_uniform_3f(name + ".lightProperty.diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
	shader2.set_uniform_3f(name + ".lightProperty.specular", m_specular[0], m_specular[1], m_specular[2]);
}
