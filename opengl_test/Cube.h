#pragma once

#include "Material.h"
#include "Shader.h"
#include <string>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Object.h"
#include <algorithm>
#include "Ray.h"

class Cube: public Object
{
public:
	Cube() = default;
	Cube(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, bool isLamp = false, float degreeAngle = 0.0f,
		Vector3 const& axis = Vector3(1.0f), float scale = 1.0f, float shininess = 32.0f, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f));
	Cube(std::string const& name, Vector3 const& translation, bool isLamp = false, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), float scale = 1.0f,
		float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f));
	static std::pair<VertexArray, unsigned int> initializeLayout();
	bool intersect(Manager const& Manager);
	bool intersectRay(Ray& ray);
	void keepTrack();

private:
	Vector4 m_minExtent;
	Vector4 m_maxExtent;
	
};