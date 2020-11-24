#pragma once

#include <vector>
#include "VertexBufferElement.h"
#include <GL/glew.h>

class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;

	VertexBufferLayout(unsigned int x, unsigned int y, unsigned int z, unsigned int t, unsigned int u);
	VertexBufferLayout(unsigned int x, unsigned int y, unsigned int z, unsigned int t);
	VertexBufferLayout(unsigned int x, unsigned int y, unsigned int z);
	VertexBufferLayout(unsigned int x, unsigned int y);
	void push(unsigned int count);
	unsigned int get_stride() const;
	std::vector<VertexBufferElement> get_elements() const;


private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};