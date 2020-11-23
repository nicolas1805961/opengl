#include "Grass.h"

float rand_uniform(float min, float max)
{
	static std::random_device generator;
	std::uniform_real_distribution<> distribution(min, max);
	return distribution(generator);
}

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

std::pair<VertexArray, unsigned int> Grass::initializeLayout()
{	
	std::vector<float> vertices{};
	auto a = Vector3(2, 0, 0).normalize();
	auto b = Vector3(0, 0, 2).normalize();
	for (size_t i = 0; i < 100000; i++)
	{
		auto x = rand_uniform(-1.0, 1.0);
		auto z = rand_uniform(-1.0, 1.0);
		vertices.push_back(x);
		vertices.push_back(0);
		vertices.push_back(z);
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(0.0f);

		auto x_axis = rand_uniform(-1.0, 1.0);
		//auto y_axis = rand_uniform(0.0, 1.0);
		auto z_axis = rand_uniform(-1.0, 1.0);

		vertices.push_back(x_axis);
		vertices.push_back(0);
		vertices.push_back(z_axis);
	}
	VertexArray vertexArray;
	VertexBuffer vb(&vertices[0], sizeof(float) * vertices.size());
	VertexBufferLayout vbl(3, 3, 3);
	vertexArray.linkVerticesAndElements(vb, vbl);
	return std::make_pair(vertexArray, vertices.size() / 2);
}