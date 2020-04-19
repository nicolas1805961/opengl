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
	Plane(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, float scale = 1.0f,
		bool isLamp = false, float degreeAngle = 0.0f, Vector3 const& axis = Vector3(1.0f), bool light = false, float shininess = 32.0f,
		float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f), Vector4 const& normal = Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	Plane(std::string const& name, Vector3 const& translation, bool isLamp = false, float scale = 1.0f, float degreeAngle = 0.0f,
		Vector3 const& axis = Vector3(1.0f), bool light = false, float shininess = 32.0f, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f), Vector4 const& normal = Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	static std::pair<VertexArray, unsigned int> initializeLayout();
	Vector4 getNormal() const;
	Vector4 getNormal();
	bool intersectRay(Ray& ray);
	void keepTrack();
	//bool intersect(Manager const& Manager);
	//bool intersectRay(int x, int y, Camera const& camera);

private:
	Vector4 m_normal;
	static unsigned int m_height;
	static unsigned int m_width;
};