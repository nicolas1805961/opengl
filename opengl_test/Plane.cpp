#include "Plane.h"

Plane::Plane()
{

}

Plane::Plane(Shader const& shader, Vector3 const& diffuse, Vector3 const& specular, float degreeAngle, Vector3 const& axis,
	Vector3 const& translation, float scale /*= 1.0f*/, float shininess /*= 32.0f*/, float mass /*= 1.0f*/,
	Vector3 const& velocity /*= Vector3(0.0f)*/, Vector3 const& normal /*= Vector3(0.0f, 1.0f, 0.0f)*/)
	: Object(shader, translation, scale, diffuse, specular, shininess, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{}

Plane::Plane(Shader const& shader, float degreeAngle, Vector3 const& axis, Vector3 const& translation, float scale /*= 1.0f*/,
	 float shininess /*= 32.0f*/, float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/,
	Vector3 const& normal /*= Vector3(0.0f, 1.0f, 0.0f)*/)
	: Object(shader, translation, scale, shininess, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{}

bool Plane::intersectRay(Ray& ray)
{
	return false;
}

std::pair<IndexBuffer, VertexArray> Plane::initializeLayout()
{
	/*static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return std::make_pair(IndexBuffer(), VertexArray());*/
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	float halfHeight = m_height / 2;
	float halfWidth = m_width / 2;
	for (size_t i = 0; i < m_height; i++)
	{
		for (size_t j = 0; j < m_width; j++)
		{
			float x = (j - halfWidth) / halfWidth;
			float y = 0;
			float z = (i - halfHeight) / halfHeight;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			vertices.push_back(0.0f);
			vertices.push_back(1.0f);
			vertices.push_back(0.0f);
		}
	}
	for (size_t i = 0; i < m_height; i++)
	{
		for (size_t j = 0; j < m_width; j++)
		{
			indices.push_back(j + i * m_width);
			indices.push_back(j + i * m_width + m_width);
			indices.push_back(j + i * m_width + 1);

			indices.push_back(j + i * m_width + 1);
			indices.push_back(j + i * m_width + m_width);
			indices.push_back(j + i * m_width + m_width + 1);
		}
	}
	VertexBuffer vb(&vertices[0], sizeof(float) * vertices.size());
	VertexBufferLayout vbl(3, 3);
	IndexBuffer ib(&indices[0], indices.size());
	VertexArray va(vb, vbl);
	return std::make_pair(ib, va);
}

Vector3 Plane::getNormal()
{
	return m_normal;
}

Vector3 Plane::getNormal() const
{
	return m_normal;
}

void Plane::draw(Matrix4f const& view, Matrix4f const& projection, unsigned int indexCount)
{
	Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);
	m_shader.set_uniform_mat_4f("view", view);
	m_shader.set_uniform_mat_4f("projection", projection);
	m_shader.set_uniform_mat_4f("model", model);
	keepTrack(model, view, projection);
	if (m_shader.getShaderType() == Shader::ShaderType::LIGHTING)
	{
		if (m_isTexture)
			m_material = Material(m_shader, m_shininess, "material");
		else
			m_material = Material(m_shader, m_shininess, "material", m_diffuse, m_specular);
	}
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	m_doesModify = false;
}

unsigned int Plane::m_height = 100.0f;

unsigned int Plane::m_width = 100.0f;
