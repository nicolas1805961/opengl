#include "Texture.h"

Texture::Texture(TextureType const& textureType)
	: m_renderer_id(0), m_local_buffer(nullptr),
	m_width(0), m_height(0), m_bpp(0), m_textureType(textureType)
{
	if (m_textureType == TextureType::DEPTH)
	{
		glGenTextures(1, &m_renderer_id);
		glBindTexture(GL_TEXTURE_2D, m_renderer_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderDepthValue[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderDepthValue);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (m_textureType == TextureType::FULL)
	{
		glGenTextures(1, &m_renderer_id);
		glBindTexture(GL_TEXTURE_2D, m_renderer_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, GL_RGB,
			GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

Texture::Texture(const std::string& path)
	: m_renderer_id(0), m_local_buffer(nullptr),
	m_width(0), m_height(0), m_bpp(0), m_textureType(TextureType::PLAIN)
{
	stbi_set_flip_vertically_on_load(1);
	m_local_buffer.reset(stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4));
	glGenTextures(1, &m_renderer_id);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer.get());
	glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::Texture(Texture const& texture)
{
	this->m_bpp = texture.m_bpp;
	this->m_height = texture.m_height;
	this->m_renderer_id = texture.m_renderer_id;
	this->m_width = texture.m_width;
	this->m_textureType = texture.m_textureType;
	this->m_local_buffer = nullptr;
}

void Texture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::get_width() const
{
	return m_width;
}


Texture::TextureType Texture::getTextureType()
{
	return m_textureType;
}

Texture::TextureType Texture::getTextureType() const
{
	return m_textureType;
}


unsigned int Texture::getId()
{
	return m_renderer_id;
}


unsigned int Texture::getId() const
{
	return m_renderer_id;
}

int Texture::get_height() const
{
	return m_height;
}

int Texture::get_bpp() const
{
	return m_bpp;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_renderer_id);
}
