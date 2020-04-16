#include "Shape.h"

Shape::Shape(std::pair<IndexBuffer, VertexArray> pair)
	: m_indexBuffer(pair.first), m_vertexArray(pair.second)
{}

bool Shape::operator==(Shape const& right)
{
	return (m_indexBuffer.getId() == right.m_indexBuffer.getId()) && (m_vertexArray.getId() == right.m_vertexArray.getId());
}

IndexBuffer Shape::getIndexBuffer()
{
	return m_indexBuffer;
}

IndexBuffer Shape::getIndexBuffer() const
{
	return m_indexBuffer;
}

VertexArray Shape::getVertexArray()
{
	return m_vertexArray;
}

VertexArray Shape::getVertexArray() const
{
	return m_vertexArray;
}
