#pragma once
#include <string>
#include <memory>
#include <GL/glew.h>
#include "stb_image.h"
#include <GL/freeglut.h>

class Texture
{
public:

	enum class TextureType {FULL, DEPTH, PLAIN};

	Texture();
	Texture(const std::string& path);
	Texture(TextureType const& textureType);
	Texture(Texture const& tecture);
	Texture& operator=(Texture const& rhs);
	void bind(unsigned int slot = 0);
	void bind(unsigned int slot = 0) const;
	void unbind();
	void unbind() const;
	int get_width() const;
	TextureType getTextureType();
	TextureType getTextureType() const;
	unsigned int getId();
	unsigned int getId() const;
	int get_height() const;
	int get_bpp() const;
	~Texture();

private:
	TextureType m_textureType;
	unsigned int m_renderer_id;
	std::unique_ptr<unsigned char[]> m_local_buffer;
	int m_width;
	int m_height;
	int m_bpp;
};