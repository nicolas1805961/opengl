#pragma once

#include <GL/glew.h>
#include "Error.h"

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void *data, GLuint scale);
	void bind() const;
	void unbind() const;
	~VertexBuffer();

private:
	GLuint m_renderer_id;
};

