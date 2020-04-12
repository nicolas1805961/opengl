#include "Sphere.h"

unsigned int Sphere::m_height = 100;
unsigned int Sphere::m_width = 100;

Sphere::Sphere(Shader const& shader, Vector3 const& diffuse, Vector3 const& specular, Vector3 const& translation, bool light /*=false*/,
	float scale /*= 1.0f*/, float shininess /*= 32.0f*/, float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/)
	: Object(shader, translation, scale, diffuse, specular, light)
{}

Sphere::Sphere(Shader const& shader, Vector3 const& translation, bool light /*=false*/, float scale /*= 1.0f*/, float shininess /*= 32.0f*/,
	float mass /*= 1.0f*/, Vector3 const& velocity /*= Vector3(0.0f)*/)
	: Object(shader, translation, scale, light)
{}

std::pair<IndexBuffer, VertexArray> Sphere::initializeLayout()
{
	/*static int callNumber = 0;
	callNumber++;
	if (callNumber > 1)
		return std::make_pair(IndexBuffer(), VertexArray());*/
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
			/*if (i != 0)
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
			}*/
			m_indices.push_back(k1);
			m_indices.push_back(k2);
			m_indices.push_back(k1 + 1);
			m_indices.push_back(k1 + 1);
			m_indices.push_back(k2);
			m_indices.push_back(k2 + 1);
			k1++;
			k2++;
		}
	}
	VertexBuffer vb(&m_vertices[0], sizeof(float) * m_vertices.size());
	VertexBufferLayout vbl(3, 3);
	IndexBuffer ib(&m_indices[0], m_indices.size());
	VertexArray va(vb, vbl);
	return std::make_pair(ib, va);
}

bool Sphere::intersectPlane(Plane const& plane)
{
	Vector3 distanceSphereCenterToPlanePoint = (m_translation - plane.getTranslation()).normalize();
	float minimalDistanceSphereToPlane = distanceSphereCenterToPlanePoint.dot_product(plane.getNormal()) / plane.getNormal().norm();
	if (minimalDistanceSphereToPlane < m_scale)
		return true;
	return false;
}

bool Sphere::intersectRay(Ray& ray)
{
	auto k = ray.get_origin() - Vector3(m_translation.get_x(), m_translation.get_y(), m_translation.get_z());
	float a = ray.get_direction().dot_product(ray.get_direction());
	float b = 2 * ray.get_direction().dot_product(k);
	float c = k.dot_product(k) - pow(m_scale, 2);
	auto discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return false;
	else if (discriminant == 0)
		ray.set_t_distance(-b / (2 * a));
	else
	{
		auto x1 = (-b - sqrt(discriminant)) / (2 * a);
		auto x2 = (-b + sqrt(discriminant)) / (2 * a);
		if (x1 < 0 && x2 < 0)
			return false;
		else if (x1 > 0 && x2 > 0)
			ray.set_t_distance(std::min(x1, x2));
		else if (x1 < 0)
			ray.set_t_distance(x2);
		else
			ray.set_t_distance(x1);
	}
	return true;
}

/*Intersect Sphere::intersectBoundingSphere(Sphere const& other)
{
	float radiusDistance = m_scale + other.m_scale;
	float centerDistance = (other.m_translation - m_translation).norm();
	if (centerDistance < radiusDistance)
		return Intersect(true, centerDistance - radiusDistance);
	else
		return Intersect(false, centerDistance - radiusDistance);
}*/

void Sphere::draw(Matrix4f const& view, Matrix4f const& projection, unsigned int indexCount)
{
	Matrix4f model(1.0f);
	model = Matrix4f::gl_translate(model, m_translation);
	model = Matrix4f::gl_scale(model, Vector3(m_scale));
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
