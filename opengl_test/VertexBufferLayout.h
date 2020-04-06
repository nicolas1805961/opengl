#pragma once

#include <vector>
#include "VertexBufferElement.h"
#include <GL/glew.h>

class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;

	VertexBufferLayout(unsigned int x, unsigned int y, unsigned int z): m_stride(0)
	{
		push<float>(x);
		push<float>(y);
		push<float>(z);
	}

	VertexBufferLayout(unsigned int x, unsigned int y): m_stride(0)
	{
		push<float>(x);
		push<float>(y);
	}

	template <typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template <>
	void push<GLfloat>(unsigned int count)
	{
		VertexBufferElement vbe(GL_FLOAT, count, GL_FALSE);
		m_elements.push_back(vbe);
		m_stride += count * vbe.get_size_of_type(GL_FLOAT);
	}

	template <>
	void push<GLuint>(unsigned int count)
	{
		VertexBufferElement vbe(GL_UNSIGNED_INT, count, GL_FALSE);
		m_elements.push_back(vbe);
		m_stride += count * vbe.get_size_of_type(GL_UNSIGNED_INT);
	}

	template <>
	void push<unsigned char>(unsigned int count)
	{
		VertexBufferElement vbe(GL_UNSIGNED_BYTE, count, GL_TRUE);
		m_elements.push_back(vbe);
		m_stride += count * vbe.get_size_of_type(GL_UNSIGNED_BYTE);
	}

	unsigned int get_stride() const { return m_stride; }
	std::vector<VertexBufferElement> get_elements() const { return m_elements; }


private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};