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
	Plane(Vector3 const& diffuse, Vector3 const& specular, float shininess,
		Vector3 const& center, float size, float degreeAngle, Vector3 const& axis, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f, 0.0f, 0.0f));
	Plane(float shininess, Vector3 const& center, float size, float degreeAngle, Vector3 const& axis, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f, 0.0f, 0.0f));
	Plane(Vector3 const& center, float size, float degreeAngle, Vector3 const& axis, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f, 0.0f, 0.0f));
	static void initializeLayout();
	//bool intersect(Objects const& objects);
	//bool intersectRay(int x, int y, Camera const& camera);

	void draw(Shader const& shader, Object::ShaderType shaderType);

private:
	Vector3 m_normal;
	static unsigned int m_height;
	static unsigned int m_width;
	float m_degreeAngle;
	Vector3 m_axis;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};