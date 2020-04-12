#include "Cube.h"

Cube::Cube() : m_degreeAngle(1.0f), m_axis(1.0f)
{

}

Cube::Cube(Shader const& shader, Vector3 const& diffuse, Vector3 const& specular, float degreeAngle, Vector3 const& axis,
	Vector3 const& translation, bool light /*= false*/, float scale /*= 1.0f*/, float shininess /*= 32.0f*/, float mass /*= 1.0f*/,
	Vector3 const& velocity /*= 0.0f*/)
	: Object(shader, translation, scale, diffuse, specular, light), m_degreeAngle(degreeAngle), m_axis(axis)
{}

Cube::Cube(Shader const& shader, float degreeAngle, Vector3 const& axis, Vector3 const& translation, bool light /*= false*/, float scale /*= 1.0f*/,
	float shininess /*= 32.0f*/, float mass /*= 1.0f*/, Vector3 const& velocity /*= 0.0f*/)
	: Object(shader, translation, scale, light), m_degreeAngle(degreeAngle), m_axis(axis)
{}

std::pair<IndexBuffer, VertexArray> Cube::initializeLayout()
{
	static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return std::make_pair(IndexBuffer(), VertexArray());
	std::vector<float> positions =
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
	VertexBuffer vb(&positions[0], positions.size() * sizeof(float));
	IndexBuffer ib(indices, 2 * 3 * 6);
	VertexBufferLayout vbl(3, 3, 2);
	VertexArray va(vb, vbl);
	return std::make_pair(ib, va);
}

bool Cube::intersectRay(Ray& ray)
{
	return true;
}

/*bool Cube::intersectRay(int x, int y, Camera const& camera)
{

}*/

void Cube::draw(Matrix4f const& view, Matrix4f const& projection, unsigned int indexCount)
{
	Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);
	keepTrack(model, view, projection);
	m_shader.set_uniform_mat_4f("view", view);
	m_shader.set_uniform_mat_4f("projection", projection);
	m_shader.set_uniform_mat_4f("model", model);
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
