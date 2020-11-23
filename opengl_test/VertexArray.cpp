#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_renderer_id);
	bind();
}


void VertexArray::linkVerticesAndElements(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout, IndexBuffer const& indexBuffer)
{
	vertexBuffer.bind();
	indexBuffer.bind();
	unsigned int offset = 0;
	auto elements = layout.get_elements();
	for (std::size_t i = 0; i < elements.size(); i++)
	{
		auto element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.get_count(), element.get_type(), element.get_normalized(), layout.get_stride(), (const void*)offset);
		offset += element.get_count() * 4;
	}
}

void VertexArray::linkVerticesAndElements(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	vertexBuffer.bind();
	unsigned int offset = 0;
	auto elements = layout.get_elements();
	for (std::size_t i = 0; i < elements.size(); i++)
	{
		auto element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.get_count(), element.get_type(), element.get_normalized(), layout.get_stride(), (const void*)offset);
		offset += element.get_count() * 4;
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(m_renderer_id);
}

bool operator==(VertexArray const& left, VertexArray const& right)
{
	return left.m_renderer_id == right.m_renderer_id;
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}


unsigned int VertexArray::getId()
{
	return m_renderer_id;
}


unsigned int VertexArray::getId() const
{
	return m_renderer_id;
}

bool VertexArray::operator<(VertexArray const& rhs)
{
	return m_renderer_id < rhs.m_renderer_id;
}

bool VertexArray::operator<(VertexArray const& rhs) const
{
	return m_renderer_id < rhs.m_renderer_id;
}

VertexArray::~VertexArray()
{
	//glDeleteVertexArrays(1, &m_renderer_id);
}