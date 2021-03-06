#include "Shader.h"

Shader::Shader(const std::string& compute_shader, ShaderType const& shaderType) : m_renderer_id(0), m_shaderType(shaderType)
{
	m_renderer_id = create_shader(get_shader(compute_shader));
}

Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader, ShaderType const& shaderType)
	: m_renderer_id(0), m_shaderType(shaderType)
{
	m_renderer_id = create_shader(get_shader(vertex_shader), get_shader(fragment_shader));
}

Shader::Shader(const std::string& vertex_shader, const std::string& geometry_shader, const std::string& fragment_shader, ShaderType const& shaderType) : m_renderer_id(0), m_shaderType(shaderType)
{
	m_renderer_id = create_shader(get_shader(vertex_shader), get_shader(geometry_shader), get_shader(fragment_shader));
}

Shader::Shader(const std::string& vertex_shader, const std::string& tessellation_control_shader, const std::string& tessellation_evaluation_shader, const std::string& fragment_shader, ShaderType const& shaderType) : m_renderer_id(0), m_shaderType(shaderType)
{
	m_renderer_id = create_shader(get_shader(vertex_shader), get_shader(tessellation_control_shader), get_shader(tessellation_evaluation_shader), get_shader(fragment_shader));
}

Shader::Shader(const std::string& vertex_shader, const std::string& tessellation_control_shader, const std::string& tessellation_evaluation_shader, const std::string& geometry_shader, const std::string& fragment_shader, ShaderType const& shaderType) : m_renderer_id(0), m_shaderType(shaderType)
{
	m_renderer_id = create_shader(get_shader(vertex_shader), get_shader(tessellation_control_shader), get_shader(tessellation_evaluation_shader), get_shader(geometry_shader), get_shader(fragment_shader));
}

void Shader::bind() const
{
	glUseProgram(m_renderer_id);
}

int Shader::get_uniform_location(const std::string& name)
{
	int location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location == -1)
		std::cerr << "Warning: uniform " << name << " does not exist !" << "\n";
	return location;
}


int Shader::get_uniform_location(const std::string& name) const
{
	int location = glGetUniformLocation(m_renderer_id, name.c_str());
	if (location == -1)
		std::cerr << "Warning: uniform " << name << " does not exist !" << "\n";
	return location;
}

void Shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}


void Shader::set_uniform_4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
	glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

void Shader::set_uniform_1f(const std::string& name, float v0)
{
	glUniform1f(get_uniform_location(name), v0);
}


void Shader::set_uniform_1f(const std::string& name, float v0) const
{
	glUniform1f(get_uniform_location(name), v0);
}

void Shader::set_uniform_3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(get_uniform_location(name), v0, v1, v2);
}


void Shader::set_uniform_3f(const std::string& name, float v0, float v1, float v2) const
{
	glUniform3f(get_uniform_location(name), v0, v1, v2);
}

void Shader::set_uniform_mat_4f(const std::string& name, Matrix4f const& matrix)
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, matrix.as_array().get());
}


void Shader::set_uniform_mat_4f(const std::string& name, Matrix4f const& matrix) const
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, matrix.as_array().get());
}

void Shader::set_uniform_1i(const std::string& name, int value)
{
	glUniform1i(get_uniform_location(name), value);
}


void Shader::set_uniform_1i(const std::string& name, int value) const
{
	glUniform1i(get_uniform_location(name), value);
}


Shader::ShaderType Shader::getShaderType()
{
	return m_shaderType;
}

Shader::ShaderType Shader::getShaderType() const
{
	return m_shaderType;
}

bool Shader::operator<(Shader const& right)
{
	return getShaderType() < right.getShaderType();
}

bool Shader::operator<(Shader const& right) const
{
	return getShaderType() < right.getShaderType();
}

bool operator==(Shader const& left, Shader const& right)
{
	return left.m_renderer_id == right.m_renderer_id;
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		auto message = std::make_unique<char[]>(length);
		glGetShaderInfoLog(id, length, &length, message.get());
		std::cerr << "FAILED TO COMPILE " << (type == GL_VERTEX_SHADER ? "VERTEX": "FRAGMENT") << " SHADER !" << "\n";
		std::cerr << message << "\n";
		glDeleteShader(id);
		return false;
	}
	return id;
}

unsigned int Shader::create_shader(const std::string& compute_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int cs = compile_shader(GL_COMPUTE_SHADER, compute_shader);
	glAttachShader(program, cs);
	glLinkProgram(program);
	GLchar ErrorLog[512] = { 0 };
	GLint size = 0;
	glGetProgramInfoLog(program, 512, &size, ErrorLog);
	std::cout << ErrorLog << "\n";
	glValidateProgram(program);
	glDeleteShader(cs);
	return program;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	GLchar ErrorLog[512] = { 0 };
	GLint size = 0;
	glGetProgramInfoLog(program, 512, &size, ErrorLog);
	std::cout << ErrorLog << "\n";
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& geometry_shader, const std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	unsigned int gs = compile_shader(GL_GEOMETRY_SHADER, geometry_shader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, gs);
	glLinkProgram(program);
	GLchar ErrorLog[512] = { 0 };
	GLint size = 0;
	glGetProgramInfoLog(program, 512, &size, ErrorLog);
	std::cout << ErrorLog << "\n";
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(gs);
	return program;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& tessellation_control_shader, const std::string& tessellation_evaluation_shader, const std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	unsigned int tcs = compile_shader(GL_TESS_CONTROL_SHADER, tessellation_control_shader);
	unsigned int tes = compile_shader(GL_TESS_EVALUATION_SHADER, tessellation_evaluation_shader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, tcs);
	glAttachShader(program, tes);
	glLinkProgram(program);
	GLchar ErrorLog[512] = { 0 };
	GLint size = 0;
	glGetProgramInfoLog(program, 512, &size, ErrorLog);
	std::cout << ErrorLog << "\n";
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(tcs);
	glDeleteShader(tes);
	return program;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& tessellation_control_shader, const std::string& tessellation_evaluation_shader, const std::string& geometry_shader, const std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	unsigned int tcs = compile_shader(GL_TESS_CONTROL_SHADER, tessellation_control_shader);
	unsigned int tes = compile_shader(GL_TESS_EVALUATION_SHADER, tessellation_evaluation_shader);
	unsigned int gs = compile_shader(GL_GEOMETRY_SHADER, geometry_shader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, tcs);
	glAttachShader(program, tes);
	glAttachShader(program, gs);
	glLinkProgram(program);
	GLchar ErrorLog[512] = { 0 };
	GLint size = 0;
	glGetProgramInfoLog(program, 512, &size, ErrorLog);
	std::cout << ErrorLog << "\n";
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(tcs);
	glDeleteShader(tes);
	glDeleteShader(gs);
	return program;
}

std::string Shader::get_shader(std::string const& filename)
{
	std::stringstream ss;
	std::ifstream input_shader(filename);
	std::string line;
	while (std::getline(input_shader, line))
		ss << line << "\n";
	return ss.str();
}

std::tuple<std::string, std::string> Shader::get_shaders(std::string const& filename)
{
	int index;
	std::string line;
	std::stringstream ss[2];
	std::ifstream input_shader(filename);
	while (std::getline(input_shader, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				index = 0;
			else if (line.find("fragment") != std::string::npos)
				index = 1;
			continue;
		}
		else
			ss[index] << line << "\n";
	}
	return { ss[0].str(), ss[1].str() };
}

Shader::~Shader()
{
	//glDeleteProgram(m_renderer_id);
}