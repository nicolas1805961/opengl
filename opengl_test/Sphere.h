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
#include "Intersect.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere(Vector3 const& diffuse, Vector3 const& specular, float shininess, Vector3 const& center, float radius);
	Sphere(float shininess, Vector3 const& center, float radius);
	Sphere(Vector3 const& center, float radius);
	static void initializeLayout();
	Intersect intersectBoundingSphere(Sphere const& other);
	void draw(Shader const& shader, Object::ShaderType shaderType);

private:
	static unsigned int m_height;
	static unsigned int m_width;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};