#include "Cube.h"

Cube::Cube(Shader const& shader, std::string const& name, Vector3 const& diffuse, Vector3 const& specular, float shininess,
	Vector3 const& center, float size, float degreeAngle, Vector3 const& axis): m_shader(shader), m_model(1.0f)
{
	m_model = Matrix4f::gl_translate(m_model, center);
	m_model = Matrix4f::gl_scale(m_model, Vector3(size));
	m_model = Matrix4f::gl_rotate(m_model, getRadians(degreeAngle), axis);
	m_shader.set_uniform_mat_4f("model", m_model);
	m_material = Material(m_shader, shininess, name, diffuse, specular);
}

Cube::Cube(Shader const& shader, std::string const& name, float shininess, Vector3 const& center, float size, float degreeAngle,
	Vector3 const& axis): m_shader(shader), m_model(1.0f)
{
	m_model = Matrix4f::gl_translate(m_model, center);
	m_model = Matrix4f::gl_scale(m_model, Vector3(size));
	m_model = Matrix4f::gl_rotate(m_model, getRadians(degreeAngle), axis);
	m_shader.set_uniform_mat_4f("model", m_model);
	m_material = Material(m_shader, shininess, name);
}

void Cube::initializeLayout()
{
	static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return;
	GLfloat positions[] =
	{
		//front
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

		//right
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//back
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

		//left
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//bottom
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

		//top
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};
	GLuint indices[] =
	{
		// front
		0, 1, 3,
		3, 1, 2,
		// right
		4, 5, 7,
		7, 5, 6,
		// back
		8, 9, 11,
		11, 9, 10,
		// left
		12, 13, 15,
		15, 13, 14,
		// bottom
		16, 17, 19,
		19, 17, 18,
		// top
		20, 21, 23,
		23, 21, 22
	};
	m_vertexBuffer = VertexBuffer(positions, 8 * 4 * 6 * sizeof(float));
	m_indexBuffer = IndexBuffer(indices, 2 * 3 * 6);
	m_vertexBufferLayout = VertexBufferLayout(3, 3, 2);
	m_vertexArray = VertexArray(m_vertexBuffer, m_vertexBufferLayout);
}

float Cube::getRadians(float degreeAngle)
{
	float y = M_PI / 180;
	return degreeAngle * y;
}

void Cube::draw(Shader const& shader) const
{
	shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Cube::draw() const
{
	m_shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

VertexBuffer Cube::m_vertexBuffer = VertexBuffer();

VertexBufferLayout Cube::m_vertexBufferLayout = VertexBufferLayout();

VertexArray Cube::m_vertexArray = VertexArray();

IndexBuffer Cube::m_indexBuffer = IndexBuffer();
