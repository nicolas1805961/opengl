#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction) : m_origin(origin), m_direction(direction), m_hit(nullptr), m_t(0), m_nearest(std::numeric_limits<float>::max())
{}

std::shared_ptr<Object> Ray::get_hit()
{
	return m_hit;
}

void Ray::set_hit(std::shared_ptr<Object> const& object)
{
	m_hit = object;
}

Vector3 Ray::get_hit_point()
{
	return m_origin + m_t * m_direction.normalize();
}

float Ray::get_t_distance()
{
	return m_t;
}

float Ray::get_t_distance() const
{
	return m_t;
}

void Ray::set_t_distance(float t)
{
	this->m_t = t;
}

void Ray::set_nearest(float nearest)
{
	this->m_nearest = nearest;
}

float Ray::get_nearest()
{
	return m_nearest;
}

float Ray::get_nearest() const
{
	return m_nearest;
}

Vector3 Ray::get_origin()
{
	return m_origin;
}

Vector3 Ray::get_origin() const
{
	return m_origin;
}

Vector3 Ray::get_direction()
{
	return m_direction.normalize();
}

Vector3 Ray::get_direction() const
{
	return m_direction.normalize();
}

Ray::~Ray() {}