#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <iostream>
#include <GL/glew.h>
#include <memory>
#include "Matrix4f.h"

class Shader
{
public:

	enum class ShaderType { SCREEN = 4, LIGHTING = 3, GRASS = 2, NORMAL=1, DEPTH = 0};

	Shader() = default;
	Shader(const std::string& vertex_shader, const std::string& fragment_shader, ShaderType const& shaderType);
	Shader(const std::string& vertex_shader, const std::string& geometry_shader, const std::string& fragment_shader, ShaderType const& shaderType);
	void bind() const;
	//void unbind() const;
	void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3);
	void set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void set_uniform_1f(const std::string& name, float v0);
	void set_uniform_1f(const std::string& name, float v0) const;
	void set_uniform_3f(const std::string& name, float v0, float v1, float v2);
	void set_uniform_3f(const std::string& name, float v0, float v1, float v2) const;
	void set_uniform_mat_4f(const std::string& name, Matrix4f const& matrix);
	void set_uniform_mat_4f(const std::string& name, Matrix4f const& matrix) const;
	void set_uniform_1i(const std::string& name, int value);
	void set_uniform_1i(const std::string& name, int value) const;
	ShaderType getShaderType();
	ShaderType getShaderType() const;
	bool operator<(Shader const& right);
	bool operator<(Shader const& right) const;
	friend bool operator==(Shader const& left, Shader const& right);
	~Shader();
	
private:
	ShaderType m_shaderType;
	unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
	unsigned int create_shader(const std::string& vertex_shader, const std::string& geometry_shader, const std::string& fragment_shader);
	std::tuple<std::string, std::string> get_shaders(std::string const& filename);
	std::string get_shader(std::string const& filename);
	int get_uniform_location(const std::string& name);
	int get_uniform_location(const std::string& name) const;
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int m_renderer_id;
};