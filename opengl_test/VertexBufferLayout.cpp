#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(unsigned int x, unsigned int y, unsigned int z) : m_stride(0)
{
	push(x);
	push(y);
	push(z);
}

VertexBufferLayout::VertexBufferLayout(unsigned int x, unsigned int y) : m_stride(0)
{
	push(x);
	push(y);
}

void VertexBufferLayout::push(unsigned int count)
{
	VertexBufferElement vbe(GL_FLOAT, count, GL_FALSE);
	m_elements.push_back(vbe);
	m_stride += count * 4;
}

unsigned int VertexBufferLayout::get_stride() const 
{ 
	return m_stride;
}

std::vector<VertexBufferElement> VertexBufferLayout::get_elements() const 
{ 
	return m_elements;
}