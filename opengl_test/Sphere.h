#pragma once

#define _USE_MATH_DEFINES

#include "Shader.h"
#include <vector>
#include <cmath>
#include <string>
#include "Vector3.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Material.h"
#include "Matrix4f.h"

class Sphere
{
public:
	Sphere(Shader const& shader, std::string const& name, Vector3 const& diffuse, Vector3 const& specular, float shininess,
		Vector3 const& center, float radius);
	Sphere(Shader const& shader, std::string const& name, float shininess, Vector3 const& center, float radius);
	static void initializeLayout();
	void draw(Shader const& shader) const;
	void draw() const;

private:
	Matrix4f m_model;
	static unsigned int m_height;
	static unsigned int m_width;
	Shader m_shader;
	Material m_material;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};