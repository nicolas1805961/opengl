#pragma once

#include <GL/glew.h>

class FrameBuffer
{
public:
	FrameBuffer();
	void attachDepthBuffer();
	void attachColorBuffer();

private:
	unsigned int m_id;
}