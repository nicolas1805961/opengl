#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_id);
	glBindRenderbuffer(GL_RENDERBUFFER, m_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

unsigned int RenderBuffer::getID()
{
	return m_id;
}

RenderBuffer::~RenderBuffer()
{
}