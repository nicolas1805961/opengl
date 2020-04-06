#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\string_cast.hpp"

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
	/*glm::mat4 view_glm = glm::lookAt(glm::vec3(this->position.get_x(), this->position.get_y(), this->position.get_z()),
		glm::vec3(this->position.get_x(), this->position.get_y(), this->position.get_z())
		+ glm::vec3(this->front.get_x(), this->front.get_y(), this->front.get_z()),
		glm::vec3(this->up.get_x(), this->up.get_y(), this->up.get_z()));
	std::cout << glm::to_string(view_glm) << "\n";*/
	return Matrix4f::gl_look_at(this->position, this->position + this->front, this->up);
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

Vector3 Camera::getFront()
{
	return this->front;
}

Vector3 Camera::GetPosition()
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
