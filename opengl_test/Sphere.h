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
	Sphere(Vector3 const& diffuse, Vector3 const& specular, float shininess, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f), Vector3 const& translation = Vector3(0.0f), float scale = 1.0f);
	Sphere(float shininess, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f), Vector3 const& translation = Vector3(0.0f), float scale = 1.0f);
	Sphere(float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f), Vector3 const& translation = Vector3(0.0f), float scale = 1.0f);
	static void initializeLayout();
	bool intersectPlane(Plane const& plane);
	//bool intersect(Objects const& objects);
	bool intersectRay(Ray& ray);
	void draw(Shader const& shader, Object::ShaderType shaderType, Matrix4f const& view, Matrix4f const& projection);

private:
	static unsigned int m_height;
	static unsigned int m_width;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};