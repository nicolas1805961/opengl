#pragma once

#include <GL/glew.h>

class VertexBufferElement
{
public:
	VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized);
	//GLuint get_size_of_type(unsigned int type);
	unsigned int get_count() const;
	unsigned int get_type() const;
	unsigned char get_normalized() const;

private:
	unsigned int m_type;
	unsigned int m_count;
	unsigned char m_normalized;
};