#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include <string.h>

class Shape
{
public:
	Shape(std::pair<VertexArray, unsigned int> pair);
	bool operator==(Shape const& right);
	VertexArray getVertexArray();
	VertexArray getVertexArray() const;
	unsigned int getIndexCount();
	unsigned int getIndexCount() const;
	
private:
	unsigned int m_indexCount;
	VertexArray m_vertexArray;
};