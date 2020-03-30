#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_renderer_id);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	unsigned int offset = 0;
	auto elements = layout.get_elements();
	for (std::size_t i = 0; i < elements.size(); i++)
	{
		auto element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.get_count(), element.get_type(), element.get_normalized(), layout.get_stride(), (const void*)offset);
		offset += element.get_count() * element.get_size_of_type(element.get_type());
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(m_renderer_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_renderer_id);
}