#include "Camera.h"

Camera::Camera(Vector3 position /*= Vector3(0.0f, 0.0f, 0.0f)*/, Vector3 up /*= Vector3(0.0f, 0.1f, 0.0f)*/,
	GLfloat yaw /*= -90.0f*/, GLfloat pitch /*= 0.0f*/)
	: front(Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(0.006f), mouseSensitivity(0.25f), zoom(45.0f)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
	:front(Vector3(0.0f, 0.0f, -1.0f)), movementSpeed(0.006f), mouseSensitivity(0.25f), zoom(45.0f)
{
	this->position = Vector3(posX, posY, posZ);
	this->worldUp = Vector3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
}

Matrix4f Camera::get_view_matrix()
{
	return Matrix4f::gl_look_at(this->position, this->position + this->front, this->up);
}

Matrix4f Camera::get_view_matrix() const
{
	return Matrix4f::gl_look_at(this->position, this->position + this->front, this->up);
}

Matrix4f Camera::getProjectionMatrix()
{
	return Matrix4f::gl_perspective(GetZoom(), 1920.0f / 1080.0f, 0.1f, 1000.0f);
}

Matrix4f Camera::getProjectionMatrix() const
{
	return Matrix4f::gl_perspective(GetZoom(), 1920.0f / 1080.0f, 0.1f, 1000.0f);
}

void Camera::ProcessKeyboard(Camera_movement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == Camera_movement::FORWARD)
		this->position += this->front * velocity;

	if (direction == Camera_movement::BACKWARD)
		this->position -= this->front * velocity;

	if (direction == Camera_movement::LEFT)
		this->position -= this->right * velocity;

	if (direction == Camera_movement::RIGHT)
		this->position += this->right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch /*= true*/)
{
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;
	this->yaw += xOffset;
	this->pitch += yOffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	/*if (constrainPitch)
	{
		if (this->pitch > 89.0f)
			this->pitch = 89.0f;

		if (this->pitch < -89.0f)
			this->pitch = -89.0f;
	}*/
	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset)
{
	if (yOffset > 0)
		this->zoom -= 0.1f;
	else if (yOffset < 0)
		this->zoom += 0.1f;
	/*if (this->zoom <= 1.0f)
		this->zoom = 1.0f;
	if (this->zoom >= 45.0f)
		this->zoom = 45.0f;*/
	/*if (this->zoom >= 1.0f && this->zoom <= 45.0f)
		this->zoom -= yOffset;

	if (this->zoom <= 1.0f)
		this->zoom = 1.0f;

	if (this->zoom >= 45.0f)
		this->zoom = 45.0f;*/
}

GLfloat Camera::GetZoom()
{
	return this->zoom;
}

GLfloat Camera::GetZoom() const
{
	return this->zoom;
}

Vector3 Camera::get3dMousePosition(int xMouse, int yMouse)
{
	float x = (2.0f * xMouse) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
	float y = 1.0f - (2.0f * yMouse) / glutGet(GLUT_WINDOW_HEIGHT);
	Vector4 to = Vector4(x, y, 1.0, 1.0);
	to = Matrix4f::inverse(getProjectionMatrix()) * to;
	to = Matrix4f::inverse(get_view_matrix()) * to;
	to.perspectiveDivision();
	Vector3 to3f = Vector3(to.get_x(), to.get_y(), to.get_z());
	return to3f;
}

Vector3 Camera::getFront()
{
	return this->front;
}

Vector3 Camera::GetPosition()
{
	return this->position;
}

Vector3 Camera::GetPosition() const
{
	return this->position;
}

GLfloat Camera::get_radians(GLfloat x)
{
	float y = M_PI / 180;
	return x * y;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	Vector3 front;
	front.set_x(cosf(get_radians(this->yaw)) * cosf(get_radians(this->pitch)));
	front.set_y(sinf(get_radians(this->pitch)));
	front.set_z(sinf(get_radians(this->yaw)) * cosf(get_radians(this->pitch)));
	this->front = front.normalize();
	// Also re-calculate the Right and Up vector
	this->right = this->front.cross_product(this->worldUp).normalize();
	this->up = this->right.cross_product(this->front).normalize();
}
