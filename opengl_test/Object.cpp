#include "Object.h"

Object::Object(std::string const& name, Vector3 const& translation, float scale, Vector3 const& diffuse, Vector3 const& specular, bool isLamp, float degreeAngle,
	Vector3 const& axis, float shininess, float mass, Vector3 const& velocity, bool isTexture, Vector3 const& acceleration,
	Vector3 const& sumForces)
	: m_translation(translation), m_scale(scale), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess), m_isTexture(isTexture),
	m_mass(mass), m_velocity(velocity), m_acceleration(acceleration), m_sumForces(sumForces),
	m_degreeAngle(degreeAngle), m_axis(axis), m_isLamp(isLamp), m_name(name), m_firstPosition(translation)
{
	keepTrack();
}

Object::Object(std::string const& name, Vector3 const& translation, float scale, bool isLamp, float degreeAngle, Vector3 const& axis, float shininess, float mass,
	Vector3 const& velocity, bool isTexture, Vector3 const& acceleration, Vector3 const& sumForces)
	: m_translation(translation), m_scale(scale), m_shininess(shininess), m_isTexture(isTexture), m_mass(mass), m_velocity(velocity),
	m_acceleration(acceleration), m_sumForces(sumForces), m_degreeAngle(degreeAngle), m_axis(axis), m_isLamp(isLamp),
	m_name(name), m_firstPosition(translation)
{
	keepTrack();
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

Vector4 Object::getPosition()
{
	return m_position;
}

Vector4 Object::getPosition() const
{
	return m_position;
}

std::string Object::getName()
{
	return m_name;
}

std::string Object::getName() const
{
	return m_name;
}

void Object::keepTrack()
{
	m_model = Matrix4f::gl_translate(Matrix4f(1.0f), m_translation);
	m_model = Matrix4f::gl_scale(m_model, Vector3(m_scale));
	m_model = Matrix4f::gl_rotate(m_model, getRadians(m_degreeAngle), m_axis);
	m_position = m_model * Vector4(0.0, 0.0, 0.0, 1.0);
	m_position.perspectiveDivision();
}

void Object::reset()
{
	m_acceleration = Vector3(0.0);
	m_sumForces = Vector3(0.0);
	m_velocity = Vector3(0.0);
}

Vector3 Object::getFirstPosition()
{
	return m_firstPosition;
}

void Object::setVelocity(float velocity)
{
	m_velocity = Vector3(velocity);
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
	default:
		break;
	}
}

void Object::setColor(Vector3 const& color)
{
	m_diffuse = color;
}

void Object::setScale(float scale)
{
	m_scale = scale;
}

void Object::updateVelocityAndPosition(float dt)
{
	Vector3 acceleration = m_sumForces / m_mass;
	Vector3 accelerationDt = acceleration * dt;
	m_velocity = m_velocity + accelerationDt;
	Vector3 velocityDt = m_velocity * dt;
	m_translation = m_translation + velocityDt;
	keepTrack();
}

void Object::setTranslation(Vector3 const& translation)
{
	m_translation = translation;
}

void Object::setPosition(Vector4 const& position)
{
	m_position = position;
}

void Object::setPosition(Vector3 const& position)
{
	m_position[0] = position[0];
	m_position[1] = position[1];
	m_position[2] = position[2];
	m_position[3] = 1.0;
}

void Object::drawLighting(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, std::pair<Matrix4f, Matrix4f> const& shadowMatrices,
	unsigned int indexCount, Shader const& shader)
{
	/*Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);*/
	//keepTrack(model, view, projection);
	shader.set_uniform_mat_4f("view", viewProjMatrices.first);
	shader.set_uniform_mat_4f("projection", viewProjMatrices.second);
	shader.set_uniform_mat_4f("model", m_model);
	shader.set_uniform_mat_4f("shadowView", shadowMatrices.first);
	shader.set_uniform_mat_4f("shadowProjection", shadowMatrices.second);
	shader.set_uniform_3f("objectDiffuse", m_diffuse.get_x(), m_diffuse.get_y(), m_diffuse.get_z());
	shader.set_uniform_3f("objectSpecular", m_specular.get_x(), m_specular.get_y(), m_specular.get_z());
	shader.set_uniform_1f("shininess", m_shininess);
	/*if (m_isTexture)
		m_material = Material(shader, m_shininess, "material");
	else
		m_material = Material(shader, m_shininess, "material", m_diffuse, m_specular);
	glViewport(0, 0, 1920, 1080);*/
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Object::drawLamp(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader)
{
	/*Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);*/
	//keepTrack(model, view, projection);
	shader.set_uniform_mat_4f("view", viewProjMatrices.first);
	shader.set_uniform_mat_4f("projection", viewProjMatrices.second);
	shader.set_uniform_mat_4f("model", m_model);
	//glViewport(0, 0, 1920, 1080);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Object::drawShadow(std::pair<Matrix4f, Matrix4f> const& viewProjMatrices, unsigned int indexCount, Shader const& shader)
{
	/*Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);*/
	//keepTrack(model, view, projection);
	shader.set_uniform_mat_4f("view", viewProjMatrices.first);
	shader.set_uniform_mat_4f("projection", viewProjMatrices.second);
	shader.set_uniform_mat_4f("model", m_model);
	//glViewport(0, 0, 1920, 1080);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

bool Object::isLamp()
{
	return m_isLamp;
}