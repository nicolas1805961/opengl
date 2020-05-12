#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

class RenderBuffer
{
public:
	RenderBuffer();
	unsigned int getID();
	~RenderBuffer();

private:
	unsigned int m_id;
};