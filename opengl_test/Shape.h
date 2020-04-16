#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include <string.h>

class Shape
{
public:
	Shape(std::pair<IndexBuffer, VertexArray> pair);
	bool operator==(Shape const& right);
	IndexBuffer getIndexBuffer();
	IndexBuffer getIndexBuffer() const;
	VertexArray getVertexArray();
	VertexArray getVertexArray() const;
	
private:
	IndexBuffer m_indexBuffer;
	VertexArray m_vertexArray;
};