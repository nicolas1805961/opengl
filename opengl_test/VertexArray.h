#pragma once

#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray() = default;
	VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
	bool operator<(VertexArray const& rhs);
	bool operator<(VertexArray const& rhs) const;
	friend bool operator==(VertexArray const& left, VertexArray const& right);
	~VertexArray();

private:
	GLuint m_renderer_id;
};