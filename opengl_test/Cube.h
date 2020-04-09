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
	Cube(Vector3 const& diffuse, Vector3 const& specular, float shininess,
		  float degreeAngle, Vector3 const& axis, float mass = 1.0f,
		Vector3 const& velocity = 0.0f, Vector3 const& translation = Vector3(0.0f), float scale = 1.0f);
	Cube(float shininess,  float degreeAngle, Vector3 const& axis, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f), Vector3 const& translation = Vector3(0.0f), float scale = 1.0f);
	Cube(  float degreeAngle, Vector3 const& axis, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f), Vector3 const& translation = Vector3(0.0f), float scale = 1.0f);
	static void initializeLayout();
	bool intersect(Objects const& objects);
	bool intersectRay(Ray& ray);

	void draw(Shader const& shader, Object::ShaderType shaderType, Matrix4f const& view, Matrix4f const& projection);
	
private:
	float m_degreeAngle;
	Vector3 m_axis;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};