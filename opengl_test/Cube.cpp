#include "Cube.h"

Cube::Cube(Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, float degreeAngle, Vector3 const& axis,
	bool light /*= false*/, float scale /*= 1.0f*/, float shininess /*= 32.0f*/, float mass /*= 1.0f*/, Vector3 const& velocity /*= 0.0f*/)
	: Object(translation, scale, diffuse, specular, light, degreeAngle, axis)
{}

Cube::Cube(Vector3 const& translation, float degreeAngle, Vector3 const& axis, bool light /*= false*/, float scale /*= 1.0f*/,
	float shininess /*= 32.0f*/, float mass /*= 1.0f*/, Vector3 const& velocity /*= 0.0f*/)
	: Object(translation, scale, light, degreeAngle, axis)
{}

std::pair<IndexBuffer, VertexArray> Cube::initializeLayout()
{
	static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return std::make_pair(IndexBuffer(), VertexArray());
	std::vector<float> positions =
	{
		//front
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

		//right
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//back
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

		//left
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//bottom
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

		//top
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};
	GLuint indices[] =
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
	VertexBuffer vb(&positions[0], positions.size() * sizeof(float));
	IndexBuffer ib(indices, 2 * 3 * 6);
	VertexBufferLayout vbl(3, 3, 2);
	VertexArray va(vb, vbl);
	return std::make_pair(ib, va);
}

bool Cube::intersectRay(Ray& ray)
{
	return true;
}

/*bool Cube::intersectRay(int x, int y, Camera const& camera)
{

}*/
