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
#include "Material.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"

class Sphere: public Object
{
public:
	Sphere(Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, bool light = false, float scale = 1.0f,
		float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f));
	Sphere(Vector3 const& translation, bool light = false, float scale = 1.0f, float degreeAngle = 0.0f,
		Vector3 const& axis = Vector3(1.0f), float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f));
	static std::pair<IndexBuffer, VertexArray> initializeLayout();
	bool intersectPlane(Plane const& plane);
	//bool intersect(Objects const& objects);
	bool intersectRay(Ray& ray);

private:
	static unsigned int m_height;
	static unsigned int m_width;
};