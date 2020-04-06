#pragma once

#include <GL/glew.h>
class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const GLuint *data, GLuint count);
	void bind() const;
	void unbind() const;
	GLuint getCount() const;
	~IndexBuffer();

private:
	GLuint m_renderer_id;
	GLuint m_count;
};

