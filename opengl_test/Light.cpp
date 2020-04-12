#include "Light.h"

Light::Light(const Shader& shader, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name,
	bool night): m_shader(shader), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_name(name), m_night(night)
{}
