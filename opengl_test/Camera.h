#pragma once

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include "Matrix4f.h"
#include <cmath>
#include <GL/freeglut.h>

class Camera
{
public:
	enum class Mouvement{FORWARD, BACKWARD, LEFT, RIGHT};

	Camera(Vector3 const& target, Vector3 const& position = Vector3(0.0f, 1.0f, 0.0f));
	void updateDirection(float x, float y);
	void updatePosition(Mouvement const& mouvement);
	Matrix4f getViewMatrix();
	float toRadian(float degreeAngle);
	float toDegree(float radianAngle);
	Vector3 get3dMousePosition(int xMouse, int yMouse);
	Matrix4f getProjectionMatrix();
	Vector3 GetPosition();
	Vector3 getDirection();

private:
	Vector3 m_target;
	float m_phi;
	float m_theta;
	Vector3 m_direction;
	Vector3 m_position;
	Vector3 m_up;
	Vector3 m_left;
};