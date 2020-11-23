#pragma once

#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	void linkVerticesAndElements(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout, IndexBuffer const& indexBuffer);
	void linkVerticesAndElements(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
	unsigned int getId();
	unsigned int getId() const;
	bool operator<(VertexArray const& rhs);
	bool operator<(VertexArray const& rhs) const;
	friend bool operator==(VertexArray const& left, VertexArray const& right);
	~VertexArray();

private:
	GLuint m_renderer_id;
};