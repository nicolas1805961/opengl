#include "Sphere.h"

unsigned int Sphere::m_height = 100;
unsigned int Sphere::m_width = 100;
IndexBuffer Sphere::m_indexBuffer = IndexBuffer();
VertexBuffer Sphere::m_vertexBuffer = VertexBuffer();
VertexBufferLayout Sphere::m_vertexBufferLayout = VertexBufferLayout();
VertexArray Sphere::m_vertexArray = VertexArray();

Sphere::Sphere(Vector3 const& diffuse, Vector3 const& specular, float shininess,
	Vector3 const& center, float radius): Object(center, radius, diffuse, specular, shininess)
{}

Sphere::Sphere(float shininess, Vector3 const& center, float radius)
	: Object(center, radius, shininess)
{}

Sphere::Sphere(Vector3 const& center, float radius): Object(center, radius)
{}

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

Intersect Sphere::intersectBoundingSphere(Sphere const& other)
{
	float radiusDistance = m_size + other.m_size;
	float centerDistance = (other.m_position - m_position).norm();
	if (centerDistance < radiusDistance)
		return Intersect(true, centerDistance - radiusDistance);
	else
		return Intersect(false, centerDistance - radiusDistance);
}

void Sphere::draw(Shader const& shader, Object::ShaderType shaderType)
{
	Matrix4f model(1.0f);
	shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	model = Matrix4f::gl_translate(model, m_position);
	model = Matrix4f::gl_scale(model, Vector3(m_size));
	shader.set_uniform_mat_4f("model", model);
	if (shaderType == Object::ShaderType::LIGHTING)
	{
		if (m_isTexture)
			m_material = Material(shader, m_shininess, "material");
		else
			m_material = Material(shader, m_shininess, "material", m_diffuse, m_specular);
	}
	glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}
