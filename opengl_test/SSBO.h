#pragma once

#include <GL/glew.h>
#include "VertexArray.h"

class SSBO
{
public:
	SSBO() = default;
	SSBO(const void* data, GLuint element_size, GLuint nb_elements, int bufferIndex);
	void bind() const;
	void unbind() const;
	GLuint getId();
	GLuint getId() const;
	unsigned int activate_vbo() const;
	unsigned int activate_vbo2D() const;
	void linkVerticesAndElements(const VertexBufferLayout& layout) const;
	~SSBO();

private:
	GLuint m_renderer_id;
	unsigned int nb_elements;
};

