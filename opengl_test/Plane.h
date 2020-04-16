#pragma once

#include "Material.h"
#include "Shader.h"
#include <string>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Object.h"
#include <algorithm>

class Plane : public Object
{
public:
	Plane();
	Plane(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, bool isLamp = false, float scale = 1.0f, float degreeAngle = 0.0f,
		Vector3 const& axis = Vector3(1.0f), bool light = false, float shininess = 32.0f, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f), Vector3 const& normal = Vector3(0.0f, 1.0f, 0.0f));
	Plane(std::string const& name, Vector3 const& translation, bool isLamp = false, float scale = 1.0f, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), bool light = false,
		float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f),
		Vector3 const& normal = Vector3(0.0f, 1.0f, 0.0f));
	static std::pair<IndexBuffer, VertexArray> initializeLayout();
	Vector3 getNormal() const;
	Vector3 getNormal();
	bool intersectRay(Ray& ray);
	//bool intersect(Manager const& Manager);
	//bool intersectRay(int x, int y, Camera const& camera);

private:
	Vector3 m_normal;
	static unsigned int m_height;
	static unsigned int m_width;
};