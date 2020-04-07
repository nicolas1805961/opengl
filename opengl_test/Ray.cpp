#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction), hit(nullptr), t(0), nearest(std::numeric_limits<float>::max())
{}

std::shared_ptr<Object> Ray::get_hit()
{
	return hit;
}

void Ray::set_hit(std::shared_ptr<Object> object)
{
	hit = object;
}

Vector3 Ray::get_hit_point()
{
	return origin + t * direction;
}

float Ray::get_t_distance()
{
	return t;
}

void Ray::set_t_distance(float t)
{
	this->t = t;
}

void Ray::set_nearest(float nearest)
{
	this->nearest = nearest;
}

float Ray::get_nearest()
{
	return nearest;
}

Vector3 Ray::get_origin()
{
	return origin;
}

Vector3 Ray::get_direction()
{
	return direction.normalize();
}

Ray::~Ray() {}