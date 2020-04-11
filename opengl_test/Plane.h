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
	Plane(Shader const& shader, Vector3 const& diffuse, Vector3 const& specular, float degreeAngle, Vector3 const& axis,
		Vector3 const& translation, float scale = 1.0f, float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f),
		Vector3 const& normal = Vector3(0.0f, 1.0f, 0.0f));
	Plane(Shader const& shader, float degreeAngle, Vector3 const& axis, Vector3 const& translation, float scale = 1.0f,
		float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f),
		Vector3 const& normal = Vector3(0.0f, 1.0f, 0.0f));
	static std::pair<IndexBuffer, VertexArray> initializeLayout();
	Vector3 getNormal() const;
	Vector3 getNormal();
	bool intersectRay(Ray& ray);
	//bool intersect(Objects const& objects);
	//bool intersectRay(int x, int y, Camera const& camera);

	void draw(Matrix4f const& view, Matrix4f const& projection, unsigned int indexCount);

private:
	Vector3 m_normal;
	static unsigned int m_height;
	static unsigned int m_width;
	float m_degreeAngle;
	Vector3 m_axis;
};