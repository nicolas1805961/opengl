#pragma once
#include <string>
#include <memory>
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture(const std::string& path);
	void bind(unsigned int slot = 0);
	void unbind();
	int get_width() const;
	int get_height() const;
	int get_bpp() const;
	~Texture();

private:
	unsigned int m_renderer_id;
	std::unique_ptr<unsigned char[]> m_local_buffer;
	std::string m_filepath;
	int m_width;
	int m_height;
	int m_bpp;
};