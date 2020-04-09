#include "Object.h"

Object::Object(Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular, float shininess, float mass,
	Vector3 const& velocity): m_translation(translation), m_scale(scale), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess),
	m_isTexture(false), m_mass(mass), m_velocity(velocity), m_acceleration(0.0f), m_sumForces(0.0f), m_doesModify(false)
{
	m_position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

Object::Object(Vector3 const& translation, float scale, float shininess, float mass, Vector3 const& velocity)
	: m_translation(translation), m_scale(scale), m_shininess(shininess), m_isTexture(true), m_mass(mass), m_velocity(velocity), m_acceleration(0.0f),
	m_sumForces(0.0f), m_doesModify(false)
{
	m_position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

Object::Object(Vector3 const& translation, float scale, float mass, Vector3 const& velocity)
	: m_translation(translation), m_scale(scale), m_isTexture(true), m_mass(mass), m_velocity(velocity), m_acceleration(0.0f),
	m_sumForces(0.0f), m_doesModify(false)
{
	m_position = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

float Object::getRadians(float degreeAngle)
{
	float y = M_PI / 180;
	return degreeAngle * y;
}

Vector3 Object::getTranslation()
{
	return m_translation;
}

Vector3 Object::getTranslation() const
{
	return m_translation;
}

void Object::keepTrack(Matrix4f const& model, Matrix4f const& view, Matrix4f const& projection)
{
	if (!m_doesModify)
		return;
	Matrix4f a = projection * view;
	Matrix4f b = a * model;
	m_position = b * m_position;
	m_position.perspectiveDivision();
	//std::cout << "position = " << m_position <<"\n";
}

float Object::getScale()
{
	return m_scale;
}

void Object::addForce(Force force)
{
	switch (force)
	{
	case Object::Force::GRAVITY:
	{
		Vector3 gravityForce = Vector3(0.0f, -9.8f, 0.0f) * m_mass;
		m_sumForces += gravityForce;
		break;
	}
	case Object::Force::FRICTION:
		break;
	default:
		break;
	}
}

void Object::setColor(Vector3 const& color)
{
	m_diffuse = color;
	m_doesModify = true;
}

void Object::setScale(float scale)
{
	m_scale = scale;
	m_doesModify = true;
}

void Object::updateVelocityAndPosition(float dt)
{
	Vector3 acceleration = m_sumForces / m_mass;
	Vector3 accelerationDt = acceleration * dt;
	m_velocity = m_velocity + accelerationDt;
	Vector3 velocityDt = m_velocity * dt;
	m_translation = m_translation + velocityDt;
	m_doesModify = true;
}

void Object::setTranslation(Vector3 const& translation)
{
	m_translation = translation;
	m_doesModify = true;
}