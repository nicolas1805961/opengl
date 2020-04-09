#include "Cube.h"

Cube::Cube() : m_degreeAngle(1.0f), m_axis(1.0f)
{

}

Cube::Cube(Vector3 const& diffuse, Vector3 const& specular, float shininess, float degreeAngle, Vector3 const& axis, float mass /*= 1.0f*/,
	Vector3 const& velocity /*= 0.0f*/, Vector3 const& translation /*= Vector3(0.0f)*/, float scale /*= 1.0f*/)
	: Object(translation, scale, diffuse, specular, shininess, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{

}

Cube::Cube(float shininess, float degreeAngle, Vector3 const& axis, float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/,
	Vector3 const& translation /*= Vector3(0.0f)*/, float scale /*= 1.0f*/)
	: Object(translation, scale, shininess, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{

}

Cube::Cube(float degreeAngle, Vector3 const& axis, float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/,
	Vector3 const& translation /*= Vector3(0.0f)*/, float scale /*= 1.0f*/)
	: Object(translation, scale, mass, velocity), m_degreeAngle(degreeAngle), m_axis(axis)
{

}

void Cube::initializeLayout()
{
	static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return;
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
	float minX, minY, minZ, maxX, maxY, maxZ;
	for (size_t i = 0; i < positions.size(); i+= 8)
	{

	}
	m_vertexBuffer = VertexBuffer(&positions[0], positions.size() * sizeof(float));
	m_indexBuffer = IndexBuffer(indices, 2 * 3 * 6);
	m_vertexBufferLayout = VertexBufferLayout(3, 3, 2);
	m_vertexArray = VertexArray(m_vertexBuffer, m_vertexBufferLayout);
}

bool Cube::intersectRay(Ray& ray)
{
	return true;
}

/*bool Cube::intersectRay(int x, int y, Camera const& camera)
{

}*/

void Cube::draw(Shader const& shader, Object::ShaderType shaderType, Matrix4f const& view, Matrix4f const& projection)
{
	Matrix4f model(1.0f);
	shader.bind();
	m_vertexArray.bind();
	m_indexBuffer.bind();
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
	model = Matrix4f::gl_rotate(model, getRadians(m_degreeAngle), m_axis);
	keepTrack(model, view, projection);
	shader.set_uniform_mat_4f("model", model);
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

VertexBuffer Cube::m_vertexBuffer = VertexBuffer();

VertexBufferLayout Cube::m_vertexBufferLayout = VertexBufferLayout();

VertexArray Cube::m_vertexArray = VertexArray();

IndexBuffer Cube::m_indexBuffer = IndexBuffer();