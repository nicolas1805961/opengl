#include "SSBO.h"

SSBO::SSBO(const void* data, GLuint element_size, GLuint nb_elements): nb_elements(nb_elements)
{
	GLuint scale = element_size * nb_elements;
	glGenBuffers(1, &m_renderer_id);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_renderer_id);
	glBufferData(GL_SHADER_STORAGE_BUFFER, scale, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_renderer_id);
}

void SSBO::bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_renderer_id);
}

void SSBO::unbind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

GLuint SSBO::getId()
{
	return m_renderer_id;
}

GLuint SSBO::getId() const
{
	return m_renderer_id;
}

void SSBO::linkVerticesAndElements(const VertexBufferLayout& layout) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
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

unsigned int SSBO::activate_vbo() const
{
	VertexArray vertexArray;
	VertexBufferLayout vbl(3, 3, 1, 1);
	linkVerticesAndElements(vbl);
	return nb_elements;
}

SSBO::~SSBO()
{
	//glDeleteBuffers(1, &m_renderer_id);
}