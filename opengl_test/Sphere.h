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

class Sphere: public Object
{
public:
	Sphere(Vector3 const& diffuse, Vector3 const& specular, float shininess, Vector3 const& center, float radius, float mass = 1.0f,
		Vector3 const& velocity = Vector3(0.0f, 0.0f, 0.0f));
	Sphere(float shininess, Vector3 const& center, float radius, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f, 0.0f, 0.0f));
	Sphere(Vector3 const& center, float radius, float mass = 1.0f, Vector3 const& velocity = Vector3(0.0f ,0.0f, 0.0f));
	static void initializeLayout();
	//bool intersect(Objects const& objects);
	//bool intersectRay(int x, int y, Camera const& camera);
	void draw(Shader const& shader, Object::ShaderType shaderType);

private:
	static unsigned int m_height;
	static unsigned int m_width;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};