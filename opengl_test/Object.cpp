#include "Object.h"

Object::Object(Shader const& shader, Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular, bool light,
	float shininess, float mass, Vector3 const& velocity, bool doesModify, bool isTexture, Vector3 const& acceleration,
	Vector3 const& sumForces, Vector4 const& position): m_shader(shader), m_translation(translation), m_scale(scale), m_diffuse(diffuse),
	m_specular(specular), m_shininess(shininess), m_isTexture(isTexture), m_mass(mass), m_velocity(velocity), m_acceleration(acceleration),
	m_sumForces(sumForces), m_doesModify(doesModify), m_light(light), m_position(position)
{}

Object::Object(Shader const& shader, Vector3 const& translation, float scale, bool light, float shininess, float mass, Vector3 const& velocity,
	bool doesModify, bool isTexture, Vector3 const& acceleration, Vector3 const& sumForces, Vector4 const& position)
	: m_shader(shader), m_translation(translation), m_scale(scale), m_shininess(shininess), m_isTexture(isTexture), m_mass(mass),
	m_velocity(velocity), m_acceleration(acceleration), m_sumForces(sumForces), m_doesModify(doesModify), m_light(light),
	m_position(position)
{}

float Object::getRadians(float degreeAngle)
{
	float y = M_PI / 180;
	return degreeAngle * y;
}

Shader Object::getShader() const
{
	return m_shader;
}

Shader Object::getShader()
{
	return m_shader;
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

bool Object::isLight()
{
	return m_light;
}

bool Object::isLight() const
{
	return m_light;
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