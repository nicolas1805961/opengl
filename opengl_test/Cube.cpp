#include "Cube.h"

Cube::Cube(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, bool isLamp /*=false*/,
	float degreeAngle, Vector3 const& axis, float scale /*= 1.0f*/, float shininess /*= 32.0f*/,
	float mass /*= 1.0f*/, Vector3 const& velocity /*= 0.0f*/)
	: Object(name, translation, scale, diffuse, specular, isLamp, degreeAngle, axis)
{
	m_minExtent = m_model * Vector4(-1.0, -1.0, 1.0, 1.0);
	m_minExtent.perspectiveDivision();
	m_maxExtent = m_model * Vector4(1.0, 1.0, -1.0, 1.0);
	m_maxExtent.perspectiveDivision();
}

Cube::Cube(std::string const& name, Vector3 const& translation, bool isLamp /*=false*/, float degreeAngle, Vector3 const& axis, float scale /*= 1.0f*/,
	float shininess /*= 32.0f*/, float mass /*= 1.0f*/, Vector3 const& velocity /*= 0.0f*/)
	: Object(name, translation, scale, isLamp, degreeAngle, axis)
{
	m_minExtent = m_model * Vector4(-1.0, -1.0, 1.0, 1.0);
	m_minExtent.perspectiveDivision();
	m_maxExtent = m_model * Vector4(1.0, 1.0, -1.0, 1.0);
	m_maxExtent.perspectiveDivision();
}

std::pair<VertexArray, unsigned int> Cube::initializeLayout()
{
	std::vector<float> positions =
	{
		//front
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

		//right
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//back
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

		//left
		-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//bottom
		-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

		//top
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};
	std::vector<unsigned int> indices =
	{
		// front
		0, 1, 3,
		3, 1, 2,
		// right
		4, 5, 7,
		7, 5, 6,
		// back
		8, 9, 11,
		11, 9, 10,
		// left
		12, 13, 15,
		15, 13, 14,
		// bottom
		16, 17, 19,
		19, 17, 18,
		// top
		20, 21, 23,
		23, 21, 22
	};
	VertexArray vertexArray;
	VertexBuffer vb(&positions[0], positions.size() * sizeof(float));
	IndexBuffer ib(&indices[0], indices.size());
	VertexBufferLayout vbl(3, 3, 2);
	vertexArray.linkVerticesAndElements(vb, vbl, ib);
	return std::make_pair(vertexArray, ib.getCount());
}

bool Cube::intersectRay(Ray& ray)
{
	Vector3 inverseDir = Vector3(1.0f) / ray.get_direction();
	float tMinX = (m_minExtent.get_x() - ray.get_origin().get_x()) * inverseDir.get_x();
	float tMaxX = (m_maxExtent.get_x() - ray.get_origin().get_x()) * inverseDir.get_x();
	float tMin = std::min(tMinX, tMaxX);
	float tMax = std::max(tMinX, tMaxX);
	float tMinY = (m_minExtent.get_y() - ray.get_origin().get_y()) * inverseDir.get_y();
	float tMaxY = (m_maxExtent.get_y() - ray.get_origin().get_y()) * inverseDir.get_y();
	tMin = std::max(tMin, std::min(tMinY, tMaxY));
	tMax = std::min(tMax, std::max(tMinY, tMaxY));
	float tMinZ = (m_minExtent.get_z() - ray.get_origin().get_z()) * inverseDir.get_z();
	float tMaxZ = (m_maxExtent.get_z() - ray.get_origin().get_z()) * inverseDir.get_z();
	tMin = std::max(tMin, std::min(tMinZ, tMaxZ));
	tMax = std::min(tMax, std::max(tMinZ, tMaxZ));
	return tMax >= tMin;
}

void Cube::keepTrack()
{
	Object::keepTrack();
	m_minExtent = m_model * Vector4(-1.0, -1.0, 1.0, 1.0);
	m_minExtent.perspectiveDivision();
	m_maxExtent = m_model * Vector4(1.0, 1.0, -1.0, 1.0);
	m_maxExtent.perspectiveDivision();
}

bool Cube::intersectPlane(Plane const& plane)
{
	Vector3 f = m_position.xyz() - m_minExtent.xyz();
	Vector3 distanceCenterToPlane = m_position.xyz() - plane.getPosition().xyz();

	float dot1 = distanceCenterToPlane.dot_product(plane.getNormal().xyz());
	float distanceCenterToPlaneProj = dot1 / plane.getNormal().xyz().norm();

	float dot2 = f.dot_product(plane.getNormal().xyz());
	float distanceCenterToEdgeProj = dot2 / plane.getNormal().xyz().norm();

	return distanceCenterToEdgeProj >= distanceCenterToPlaneProj;
}
