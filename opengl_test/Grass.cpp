#include "Grass.h"

Grass::Grass()
{}

Grass::Grass(std::string const& name, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, float scale /*= 1.0*/,
	bool isLamp /*=false*/, float degreeAngle, Vector3 const& axis, bool light /*=false*/, float shininess /*= 32.0*/)
	: Object(name, translation, scale, diffuse, specular, isLamp, degreeAngle, axis)
{}

Grass::Grass(std::string const& name, Vector3 const& translation, bool isLamp /*=false*/, float scale /*= 1.0*/, float degreeAngle,
	Vector3 const& axis, bool light /*=false*/, float shininess /*= 32.0*/)
	: Object(name, translation, scale, isLamp, degreeAngle, axis)
{}

void Grass::keepTrack()
{
	Object::keepTrack();
}

bool Grass::intersectRay(Ray& ray)
{
	return false;
}

bool Grass::intersectPlane(Plane const& plane)
{
	return true;
}

std::pair<VertexArray, unsigned int> Grass::initializeLayout(Random & rand_generator)
{	
	std::vector<float> vertices{};
	auto a = Vector3(2, 0, 0).normalize();
	auto b = Vector3(0, 0, 2).normalize();
	for (size_t i = 0; i < m_grass_density; i++)
	{
		auto x = rand_generator.rand_uniform(-1.0, 1.0);
		auto z = rand_generator.rand_uniform(-1.0, 1.0);
		vertices.push_back(x);
		vertices.push_back(0);
		vertices.push_back(z);

		auto x_up = rand_generator.rand_normal(0, 0.3, false, false);
		auto y_up = rand_generator.rand_normal(0.8, 0.01, true, false);
		auto z_up = rand_generator.rand_normal(0, 0.3, false, false);

		vertices.push_back(x_up);
		vertices.push_back(y_up);
		vertices.push_back(z_up);

		auto x_axis = rand_generator.rand_normal(0.0005, 0.001, true, true);
		auto z_axis = rand_generator.rand_normal(0.0005, 0.001, true, true);

		vertices.push_back(x_axis);
		vertices.push_back(0);
		vertices.push_back(z_axis);

		vertices.push_back(rand_generator.rand_normal(0.02, 0.01, true, false));
	}
	VertexArray vertexArray;
	VertexBuffer vb(&vertices[0], sizeof(float) * vertices.size());
	VertexBufferLayout vbl(3, 3, 3, 1);
	vertexArray.linkVerticesAndElements(vb, vbl);
	return std::make_pair(vertexArray, m_grass_density);
}

unsigned int Grass::m_grass_density = 10000;