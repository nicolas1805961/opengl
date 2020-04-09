#include "Plane.h"

Plane::Plane()
{

}

Plane::Plane(Vector3 const& diffuse, Vector3 const& specular, float shininess, float degreeAngle, Vector3 const& axis,
	float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/, Vector3 const& translation /*= Vector3(0.0f)*/, float scale /*= 1.0f*/,
	Vector3 const& normal /*= Vector3(0.0f, 1.0f, 0.0f)*/)
	: Object(translation, scale, diffuse, specular, shininess, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{

}

Plane::Plane(float shininess, float degreeAngle, Vector3 const& axis, float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/,
	Vector3 const& translation /*= Vector3(0.0f)*/, float scale /*= 1.0f*/, Vector3 const& normal /*= Vector3(0.0f, 1.0f, 0.0f)*/)
	: Object(translation, scale, shininess, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{

}

Plane::Plane(float degreeAngle, Vector3 const& axis, float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/,
	Vector3 const& translation /*= Vector3(0.0f)*/, float scale /*= 1.0f*/, Vector3 const& normal /*= Vector3(0.0f, 1.0f, 0.0f)*/)
	: Object(translation, scale, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{

}

bool Plane::intersectRay(Ray& ray)
{
	return false;
}

void Plane::initializeLayout()
{
	static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return;
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
	m_vertexBuffer = VertexBuffer(&vertices[0], sizeof(float) * vertices.size());
	m_vertexBufferLayout = VertexBufferLayout(3, 3);
	m_indexBuffer = IndexBuffer(&indices[0], indices.size());
	m_vertexArray = VertexArray(m_vertexBuffer, m_vertexBufferLayout);
}

Vector3 Plane::getNormal()
{
	return m_normal;
}

Vector3 Plane::getNormal() const
{
	return m_normal;
}

void Plane::draw(Shader const& shader, Object::ShaderType shaderType, Matrix4f const& view, Matrix4f const& projection)
{
	Matrix4f model(1.0f);
	shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);
	shader.set_uniform_mat_4f("model", model);
	keepTrack(model, view, projection);
	if (shaderType == Object::ShaderType::LIGHTING)
	{
		if (m_isTexture)
			m_material = Material(shader, m_shininess, "material");
		else
			m_material = Material(shader, m_shininess, "material", m_diffuse, m_specular);
	}
	glDrawElements(GL_TRIANGLES, m_indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	m_doesModify = false;
}

unsigned int Plane::m_height = 100.0f;

unsigned int Plane::m_width = 100.0f;

VertexBuffer Plane::m_vertexBuffer = VertexBuffer();

VertexBufferLayout Plane::m_vertexBufferLayout = VertexBufferLayout();

VertexArray Plane::m_vertexArray = VertexArray();

IndexBuffer Plane::m_indexBuffer = IndexBuffer();
