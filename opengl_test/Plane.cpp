#include "Plane.h"

Plane::Plane()
{

}

Plane::Plane(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, float scale /*= 1.0*/,
	bool isLamp /*=false*/, float degreeAngle, Vector3 const& axis, bool light /*=false*/, float shininess /*= 32.0*/,
	float mass /*= 1.0*/, Vector3 const& velocity /*= Vector3(0.0)*/, Vector4 const& normal /*= Vector4(0.0, 1.0, 0.0, 1.0)*/)
	: Object(name, translation, scale, diffuse, specular, isLamp, degreeAngle, axis), m_normal(normal)
{}

Plane::Plane(std::string const& name, Vector3 const& translation, bool isLamp /*=false*/, float scale /*= 1.0*/, float degreeAngle,
	Vector3 const& axis, bool light /*=false*/, float shininess /*= 32.0*/, float mass /*= 1.0*/,
	Vector3 const& velocity /*= Vector3(0.0)*/, Vector4 const& normal /*= Vector4(0.0, 1.0, 0.0, 1.0)*/)
	: Object(name, translation, scale, isLamp, degreeAngle, axis), m_normal(normal)
{}

bool Plane::intersectRay(Ray& ray)
{
	return false;
}

void Plane::keepTrack()
{
	Object::keepTrack();
	m_normal = m_model * Vector4(0.0, 1.0, 0.0, 1.0);
	m_normal.perspectiveDivision();
}

bool Plane::intersectPlane(Plane const& plane)
{
	return true;
}

std::pair<VertexArray, unsigned int> Plane::initializeLayout()
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;
	for (size_t i = 0; i < m_height; i++)
	{
		for (size_t j = 0; j < m_width; j++)
		{
			float u = j / m_width;
			float v = i / m_height;
			float x = (j - halfWidth) / halfWidth;
			float y = 0;
			float z = (i - halfHeight) / halfHeight;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			vertices.push_back(0.0f);
			vertices.push_back(1.0f);
			vertices.push_back(0.0f);
			vertices.push_back(u);
			vertices.push_back(v);
		}
	}
	for (size_t i = 0; i < m_height; i++)
	{
		for (size_t j = 0; j < m_width; j++)
		{
			indices.push_back(j + i * m_width);
			indices.push_back(j + i * m_width + m_width);
			indices.push_back(j + i * m_width + 1);

			indices.push_back(j + i * m_width + 1);
			indices.push_back(j + i * m_width + m_width);
			indices.push_back(j + i * m_width + m_width + 1);
		}
	}
	VertexArray vertexArray;
	VertexBuffer vb(&vertices[0], sizeof(float) * vertices.size());
	IndexBuffer ib(&indices[0], indices.size());
	VertexBufferLayout vbl(3, 3, 2);
	vertexArray.linkVerticesAndElements(vb, vbl, ib);
	return std::make_pair(vertexArray, ib.getCount());
}

Vector4 Plane::getNormal()
{
	return m_normal;
}

Vector4 Plane::getNormal() const
{
	return m_normal;
}

unsigned int Plane::m_height = 50.0f;

unsigned int Plane::m_width = 50.0f;
