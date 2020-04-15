#include "Object.h"

Object::Object(Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular, bool light, float degreeAngle,
	Vector3 const& axis, float shininess, float mass, Vector3 const& velocity, bool doesModify, bool isTexture, Vector3 const& acceleration,
	Vector3 const& sumForces, Vector4 const& position)
	: m_translation(translation), m_scale(scale), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess), m_isTexture(isTexture),
	m_mass(mass), m_velocity(velocity), m_acceleration(acceleration), m_sumForces(sumForces), m_doesModify(doesModify), m_light(light),
	m_position(position), m_degreeAngle(degreeAngle), m_axis(axis)
{}

Object::Object(Vector3 const& translation, float scale, bool light, float degreeAngle, Vector3 const& axis, float shininess, float mass,
	Vector3 const& velocity, bool doesModify, bool isTexture, Vector3 const& acceleration, Vector3 const& sumForces,
	Vector4 const& position)
	: m_translation(translation), m_scale(scale), m_shininess(shininess), m_isTexture(isTexture), m_mass(mass), m_velocity(velocity),
	m_acceleration(acceleration), m_sumForces(sumForces), m_doesModify(doesModify), m_light(light), m_position(position),
	m_degreeAngle(degreeAngle), m_axis(axis)
{}

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

void Object::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	unsigned int indexCount, Shader const& shader)
{
	Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);
	//keepTrack(model, view, projection);
	shader.set_uniform_mat_4f("view", viewProjMatrices.first);
	shader.set_uniform_mat_4f("projection", viewProjMatrices.second);
	shader.set_uniform_mat_4f("model", model);
	shader.set_uniform_mat_4f("shadowView", shadowMatrices.first);
	shader.set_uniform_mat_4f("shadowProjection", shadowMatrices.second);
	if (m_isTexture)
		m_material = Material(shader, m_shininess, "material");
	else
		m_material = Material(shader, m_shininess, "material", m_diffuse, m_specular);
	//glViewport(0, 0, 1920, 1080);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	m_doesModify = false;
}

void Object::draw(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader)
{
	Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);
	//keepTrack(model, view, projection);
	shader.set_uniform_mat_4f("view", viewProjMatrices.first);
	shader.set_uniform_mat_4f("projection", viewProjMatrices.second);
	shader.set_uniform_mat_4f("model", model);
	//glViewport(0, 0, 1920, 1080);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	m_doesModify = false;
}
