#include "Camera.h"

Camera::Camera(Vector3 const& target, Vector3 const& position)
	: m_target(target), m_position(position), m_up(0.0f, 1.0f, 0.0f)
{
	m_direction = (m_target - position).normalize();
	m_left = m_up.cross_product(m_direction).normalize();
	m_phi = toDegree(asin(m_direction.get_y()));
	m_theta = toDegree(atan2(m_direction.get_z(), m_direction.get_x()));
}

void Camera::updateDirection(float x, float y)
{
	m_theta += (x * 0.5);
	m_phi += (y * 0.5);
	//std::cout << m_longitude << "\n";
	if (m_phi >= 89.0f)
		m_phi = 89.0f;
	else if (m_phi <= -89.0f)
		m_phi = -89.0f;
	m_direction[0] = cos(toRadian(m_phi)) * cos(toRadian(m_theta));
	m_direction[1] = sin(toRadian(m_phi));
	m_direction[2] = sin(toRadian(m_theta)) * cos(toRadian(m_phi));
	m_direction = m_direction.normalize();
	m_left = m_up.cross_product(m_direction).normalize();
	m_target = m_direction + m_position;
}

void Camera::updatePosition(Mouvement const& mouvement)
{
	if (mouvement == Mouvement::FORWARD)
		m_position += m_direction * 0.25;
	if (mouvement == Mouvement::BACKWARD)
		m_position -= m_direction * 0.25;
	if (mouvement == Mouvement::LEFT)
		m_position += m_left * 0.25;
	if (mouvement == Mouvement::RIGHT)
		m_position -= m_left * 0.25;
	m_target = m_direction + m_position;
}

Matrix4f Camera::getViewMatrix()
{
	return Matrix4f::gl_look_at(m_position, m_target, m_up);
}

float Camera::toRadian(float degreeAngle)
{
	float y = M_PI / 180;
	return degreeAngle * y;
}

float Camera::toDegree(float radianAngle)
{
	float y = 180 / M_PI;
	return radianAngle * y;
}

Vector3 Camera::get3dMousePosition(int xMouse, int yMouse)
{
	float x = (2.0f * xMouse) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
	float y = 1.0f - (2.0f * yMouse) / glutGet(GLUT_WINDOW_HEIGHT);
	Vector4 to = Vector4(x, y, 1.0, 1.0);
	to = Matrix4f::inverse(getProjectionMatrix()) * to;
	to = Matrix4f::inverse(getViewMatrix()) * to;
	to.perspectiveDivision();
	Vector3 to3f = Vector3(to.get_x(), to.get_y(), to.get_z());
	return to3f;
}

Matrix4f Camera::getProjectionMatrix()
{
	return Matrix4f::gl_perspective(45, 1920.0f / 1080.0f, 0.1f, 1000.0f);
}

Vector3 Camera::GetPosition()
{
	return m_position;
}

Vector3 Camera::getDirection()
{
	return m_direction;
}
