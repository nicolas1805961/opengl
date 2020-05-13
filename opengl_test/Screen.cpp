#include "Screen.h"


Screen::Screen()
{
}

std::pair<VertexArray, unsigned int> Screen::initializeLayout()
{
	std::vector<float> positions =
	{
		-1.0, 1.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 0.0,
		1.0, -1.0, 1.0, 0.0,
		1.0, 1.0, 1.0, 1.0,
	};
	std::vector<unsigned int> indices =
	{
		0, 1, 3,
		3, 1, 2,
	};
	VertexArray vertexArray;
	VertexBuffer vb(&positions[0], positions.size() * sizeof(float));
	IndexBuffer ib(&indices[0], indices.size());
	VertexBufferLayout vbl(2, 2);
	vertexArray.linkVerticesAndElements(vb, vbl, ib);
	return std::make_pair(vertexArray, ib.getCount());
}

Screen::~Screen()
{
}