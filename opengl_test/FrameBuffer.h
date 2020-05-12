#pragma once

#include <GL/glew.h>
#include "Matrix4f.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer
{
public:
	FrameBuffer(Texture const& texture);
	void bind();
	void bind() const;
	void unbind();
	void unbind() const;
	void bind(unsigned int id);
	void bind(unsigned int id) const;
	void bindTexture();
	void bindTexture() const;
	void unbindTexture();
	void unbindTexture() const;
	unsigned int getId();
	unsigned int getId() const;

private:
	Texture m_texture;
	RenderBuffer m_renderBuffer;
	unsigned int m_id;
};