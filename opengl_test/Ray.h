#pragma once

#include "Vector3.h"
#include "Object.h"
#include <memory>
#include <limits>

class Ray
{
private:
	Vector3 origin;
	Vector3 direction;
	std::shared_ptr<Object> hit;
	float t;
	float nearest;

public:
	Ray(Vector3 origin, Vector3 direction);
	std::shared_ptr<Object> get_hit();
	void set_hit(std::shared_ptr<Object> object);
	Vector3 get_hit_point();
	float get_t_distance();
	void set_t_distance(float t);
	void set_nearest(float nearest);
	float get_nearest();
	Vector3 get_origin();
	Vector3 get_direction();
	~Ray();
};


