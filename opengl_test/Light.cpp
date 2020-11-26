#include "Light.h"

Light::Light(const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, std::string const& name)
	: m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_name(name)
{}
