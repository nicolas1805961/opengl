#include "Shape.h"

Shape::Shape(std::pair<VertexArray, unsigned int> pair)
	: m_vertexArray(pair.first), m_indexCount(pair.second)
{}

bool Shape::operator==(Shape const& right)
{
	return (m_vertexArray.getId() == right.m_vertexArray.getId());
}

VertexArray Shape::getVertexArray()
{
	return m_vertexArray;
}

VertexArray Shape::getVertexArray() const
{
	return m_vertexArray;
}

unsigned int Shape::getIndexCount()
{
	return m_indexCount;
}

unsigned int Shape::getIndexCount() const
{
	return m_indexCount;
}
