#pragma once

#include <GL/glew.h>
class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const GLuint *data, GLuint count);
	void bind() const;
	void unbind() const;
	unsigned int getId();
	unsigned int getId() const;
	GLuint getCount() const;
	friend bool operator==(IndexBuffer const& left, IndexBuffer const& right);
	bool operator<(IndexBuffer const& right);
	bool operator<(IndexBuffer const& right) const;
	~IndexBuffer();

private:
	GLuint m_renderer_id;
	GLuint m_count;
};

