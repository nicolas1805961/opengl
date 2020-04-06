#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <iostream>
#include <GL/glew.h>
#include <memory>
#include "Matrix4f.h"
#include "glm\glm.hpp"

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertex_shader, const std::string& fragment_shader);
	void bind() const;
	void unbind() const;
	void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
	void set_uniform_1f(const std::string& name, float v0);
	void set_uniform_3f(const std::string& name, float v0, float v1, float v2);
	void set_uniform_mat_4f(const std::string& name, Matrix4f& matrix);
	void set_uniform_mat_4f_glm(const std::string& name, const glm::mat4& matrix);
	void set_uniform_1i(const std::string& name, int value);
	~Shader();
	
private:
	unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
	std::tuple<std::string, std::string> get_shaders(std::string const& filename);
	std::string get_shader(std::string const& filename);
	int get_uniform_location(const std::string& name);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int m_renderer_id;
};
