#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint* data, GLuint count): m_count(count)
{
	glGenBuffers(1, &m_renderer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


GLuint IndexBuffer::getCount() const
{
	return m_count;
}

IndexBuffer::~IndexBuffer()
{
	//glDeleteBuffers(1, &m_renderer_id);
}
