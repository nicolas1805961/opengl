#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(Texture const& texture): m_texture(texture)
{
	glGenFramebuffers(1, &m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
	if (texture.getTextureType() == Texture::TextureType::DEPTH)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.getId(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void FrameBuffer::bind(unsigned int id)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBuffer::bind(unsigned int id) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBuffer::bindTexture()
{
	m_texture.bind();
}

void FrameBuffer::bindTexture() const
{
	m_texture.bind();
}

void FrameBuffer::unbindTexture()
{
	m_texture.unbind();
}

void FrameBuffer::unbindTexture() const
{
	m_texture.unbind();
}

unsigned int FrameBuffer::getId()
{
	return m_id;
}

unsigned int FrameBuffer::getId() const
{
	return m_id;
}
