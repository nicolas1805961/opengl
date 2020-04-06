#include "Object.h"

Object::Object(Vector3 const& position, float size, Vector3 const& diffuse, Vector3 const& specular, float shininess)
	: m_position(position), m_size(size), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess), m_isTexture(false)
{}

Object::Object(Vector3 const& position, float size, float shininess)
	: m_position(position), m_size(size), m_shininess(shininess), m_isTexture(true)
{}

Object::Object(Vector3 const& position, float size): m_position(position), m_size(size), m_isTexture(true)
{}

float Object::getRadians(float degreeAngle)
{
	float y = M_PI / 180;
	return degreeAngle * y;
}

Vector3 Object::getPosition()
{
	return m_position;
}

float Object::getSize()
{
	return m_size;
}

void Object::setSize(float size)
{
	m_size = size;
}

void Object::setPosition(Vector3 const& position)
{
	m_position = position;
}
