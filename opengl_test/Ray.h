#pragma once

#include "Vector3.h"
#include "Object.h"
#include <memory>
#include <limits>

class Object;

class Ray
{
private:
	Vector3 m_origin;
	Vector3 m_direction;
	std::shared_ptr<Object> m_hit;
	float m_t;
	float m_nearest;

public:
	Ray() = default;
	Ray(Vector3 origin, Vector3 direction);
	std::shared_ptr<Object> get_hit();
	void set_hit(std::shared_ptr<Object> const& object);
	Vector3 get_hit_point();
	float get_t_distance();
	float get_t_distance() const;
	void set_t_distance(float t);
	void set_nearest(float nearest);
	float get_nearest();
	float get_nearest() const;
	Vector3 get_origin();
	Vector3 get_origin() const;
	Vector3 get_direction();
	Vector3 get_direction() const;
	~Ray();
};


