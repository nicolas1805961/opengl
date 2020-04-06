#include "Sphere.h"

unsigned int Sphere::m_height = 100;
unsigned int Sphere::m_width = 100;
IndexBuffer Sphere::m_indexBuffer = IndexBuffer();
VertexBuffer Sphere::m_vertexBuffer = VertexBuffer();
VertexBufferLayout Sphere::m_vertexBufferLayout = VertexBufferLayout();
VertexArray Sphere::m_vertexArray = VertexArray();

Sphere::Sphere(Shader const& shader, std::string const& name, Vector3 const& diffuse, Vector3 const& specular, float shininess,
	Vector3 const& center, float radius): m_shader(shader), m_model(1.0f)
{
	m_model = Matrix4f::gl_translate(m_model, center);
	m_model = Matrix4f::gl_scale(m_model, Vector3(radius));
	m_shader.set_uniform_mat_4f("model", m_model);
	m_material = Material(m_shader, shininess, name, diffuse, specular);
}

Sphere::Sphere(Shader const& shader, std::string const& name, float shininess, Vector3 const& center, float radius)
	: m_shader(shader), m_model(1.0f)
{
	m_model = Matrix4f::gl_translate(m_model, center);
	m_model = Matrix4f::gl_scale(m_model, Vector3(radius));
	m_shader.set_uniform_mat_4f("model", m_model);
	m_material = Material(m_shader, shininess, name);
}

void Sphere::initializeLayout()
{
	static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return;
	std::vector<unsigned int> m_indices;
	std::vector<float> m_vertices;
	unsigned int k1;
	unsigned int k2;
	for (size_t i = 0; i <= m_height; i++)
	{
		float phi = (M_PI / 2) * M_PI * i / m_height;
		for (size_t j = 0; j <= m_width; j++)
		{
			float theta = 2 * M_PI * j / m_width;
			float x = cosf(phi) * cosf(theta);
			float y = sinf(phi);
			float z = cosf(phi) * sinf(theta);
			float nx = x;
			float ny = y;
			float nz = z;
			m_vertices.push_back(x);
			m_vertices.push_back(y);
			m_vertices.push_back(z);
			m_vertices.push_back(nx);
			m_vertices.push_back(ny);
			m_vertices.push_back(nz);
		}
	}

	for (size_t i = 0; i < m_height; i++)
	{
		k1 = i * (m_width + 1);
		k2 = k1 + m_width + 1;
		for (size_t j = 0; j < m_width; j++)
		{
			if (i != 0)
			{
				m_indices.push_back(k1);
				m_indices.push_back(k2);
				m_indices.push_back(k1 + 1);
			}
			if (i != m_height - 1)
			{
				m_indices.push_back(k1 + 1);
				m_indices.push_back(k2);
				m_indices.push_back(k2 + 1);
			}
			k1++;
			k2++;
		}
	}
	m_vertexBuffer = VertexBuffer(&m_vertices[0], sizeof(float) * m_vertices.size());
	m_vertexBufferLayout = VertexBufferLayout(3, 3);
	m_indexBuffer = IndexBuffer(&m_indices[0], m_indices.size());
	m_vertexArray = VertexArray(m_vertexBuffer, m_vertexBufferLayout);
}

void Sphere::draw() const
{
	m_shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Sphere::draw(Shader const& shader) const
{
	shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}
