#pragma once

#define _USE_MATH_DEFINES

#include "Shader.h"
#include <vector>
#include <cmath>
#include <string>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"

class Sphere: public Object
{
public:
	Sphere(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, bool isLamp = false,
		 float scale = 1.0f, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f,
		float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f));
	Sphere(std::string const& name, Vector3 const& translation, bool isLamp = false, float scale = 1.0f,
		float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f));
	static std::pair<VertexArray, unsigned int> initializeLayout();
	bool intersectPlane(Plane const& plane);
	//bool intersect(Manager const& Manager);
	bool intersectRay(Ray& ray);
	void keepTrack();

private:
	static unsigned int m_height;
	static unsigned int m_width;
};