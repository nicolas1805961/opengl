#pragma once

#include <GL/glew.h>
class VertexBuffer
{
public:
	VertexBuffer(const void *data, GLuint size);
	void bind() const;
	void unbind() const;
	~VertexBuffer();

private:
	GLuint m_renderer_id;
};

