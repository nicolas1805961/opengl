#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <GL/glew.h>
#include "Vector3.h"
#include "Matrix4f.h"

enum class Camera_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

/*const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;*/

class Camera
{
public:
	Camera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 0.1f, 0.0f),
		GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);
	Camera(GLfloat posX = 0.0f, GLfloat posY = 0.0f, GLfloat posZ = 0.0f, GLfloat upX = 0.0f, GLfloat upY = 1.0f,
		GLfloat upZ = 0.0f, GLfloat yaw = -90.0f, GLfloat pitch = 0.0f);
	Matrix4f get_view_matrix();
	void ProcessKeyboard(Camera_movement direction, GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(GLfloat yOffset);
	GLfloat GetZoom();
	Vector3 GetPosition();
	GLfloat get_radians(GLfloat x);
	
private:
	// Camera Attributes
	Vector3 position;
	Vector3 front;
	Vector3 up;
	Vector3 right;
	Vector3 worldUp;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;

	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;
	void updateCameraVectors();
};