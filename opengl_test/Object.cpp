#include "Object.h"

Object::Object(Vector3 const& position, float size, Vector3 const& diffuse, Vector3 const& specular, float shininess, float mass,
	Vector3 const& velocity): m_position(position), m_size(size), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess),
	m_isTexture(false), m_mass(mass), m_velocity(velocity)
{
	m_force = Vector3(0.0f, m_mass * -9.81, 0.0f);
}

Object::Object(Vector3 const& position, float size, float shininess, float mass, Vector3 const& velocity)
	: m_position(position), m_size(size), m_shininess(shininess), m_isTexture(true), m_mass(mass), m_velocity(velocity)
{
	m_force = Vector3(0.0f, m_mass * -9.81, 0.0f);
}

Object::Object(Vector3 const& position, float size, float mass, Vector3 const& velocity)
	: m_position(position), m_size(size), m_isTexture(true), m_mass(mass), m_velocity(velocity)
{
	m_force = Vector3(0.0f, m_mass * -9.81, 0.0f);
}

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

void Object::updateVelocityAndPosition(float dt)
{
	Vector3 acceleration = m_force / m_mass;
	Vector3 accelerationDt = acceleration * dt;
	m_velocity = m_velocity + accelerationDt;
	Vector3 velocityDt = m_velocity * dt;
	m_position = m_position + velocityDt;
}

void Object::setPosition(Vector3 const& position)
{
	m_position = position;
}
