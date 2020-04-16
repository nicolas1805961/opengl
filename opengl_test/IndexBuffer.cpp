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


unsigned int IndexBuffer::getId()
{
	return m_renderer_id;
}


unsigned int IndexBuffer::getId() const
{
	return m_renderer_id;
}

GLuint IndexBuffer::getCount() const
{
	return m_count;
}

bool operator==(IndexBuffer const& left, IndexBuffer const& right)
{
	return left.m_renderer_id == right.m_renderer_id;
}


bool IndexBuffer::operator<(IndexBuffer const& right)
{
	return m_renderer_id < right.m_renderer_id;
}

bool IndexBuffer::operator<(IndexBuffer const& right) const
{
	return m_renderer_id < right.m_renderer_id;
}

IndexBuffer::~IndexBuffer()
{
	//glDeleteBuffers(1, &m_renderer_id);
}
