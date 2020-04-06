#pragma once

#include "Material.h"
#include "Shader.h"
#include <string>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Object.h"

class Cube: public Object
{
public:
	Cube();
	Cube(Vector3 const& diffuse, Vector3 const& specular, float shininess,
		Vector3 const& center, float size, float degreeAngle, Vector3 const& axis);
	Cube(float shininess, Vector3 const& center, float size, float degreeAngle, Vector3 const& axis);
	Cube(Vector3 const& center, float size, float degreeAngle, Vector3 const& axis);
	static void initializeLayout();
	void draw(Shader const& shader, Object::ShaderType shaderType);
	
private:
	float m_degreeAngle;
	Vector3 m_axis;
	static VertexBuffer m_vertexBuffer;
	static VertexBufferLayout m_vertexBufferLayout;
	static VertexArray m_vertexArray;
	static IndexBuffer m_indexBuffer;
};