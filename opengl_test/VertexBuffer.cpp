#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, GLuint scale)
{
	glGenBuffers(1, &m_renderer_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ARRAY_BUFFER, scale, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	//glDeleteBuffers(1, &m_renderer_id);
}
