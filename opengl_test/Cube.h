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
	Cube();
	Cube(Shader const& shader, Vector3 const& diffuse, Vector3 const& specular, float degreeAngle, Vector3 const& axis, 
		Vector3 const& translation, float scale = 1.0f, float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = 0.0f);
	Cube(Shader const& shader, float degreeAngle, Vector3 const& axis, Vector3 const& translation, float scale = 1.0f,
		float shininess = 32.0f, float mass = 1.0f, Vector3 const& velocity = 0.0f);
	static std::pair<IndexBuffer, VertexArray> initializeLayout();
	bool intersect(Objects const& objects);
	bool intersectRay(Ray& ray);

	void draw(Matrix4f const& view, Matrix4f const& projection, unsigned int indexCount);
	
private:
	float m_degreeAngle;
	Vector3 m_axis;
};