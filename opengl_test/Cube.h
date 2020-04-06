#pragma once

#define _USE_MATH_DEFINES

#include "Material.h"
#include "Vector3.h"
#include "Shader.h"
#include <string>
#include <cmath>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Matrix4f.h"

class Cube
{
public:
	Cube(Shader const& shader, std::string const& name, Vector3 const& diffuse, Vector3 const& specular, float shininess,
		Vector3 const& center, float size, float degreeAngle, Vector3 const& axis);
	Cube(Shader const& shader, std::string const& name, float shininess, Vector3 const& center, float size, float degreeAngle,
		Vector3 const& axis);
	static void initializeLayout();
	float getRadians(float degreeAngle);
	void draw(Shader const& shader) const;
	void draw() const;
	
private:
	Matrix4f m_model;
	Shader m_shader;
	Material m_material;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};