#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

class Vector2
{
private:
	float x;
	float y;

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(float f);
	Vector2 operator+(Vector2 const& rhs);
	Vector2 operator*(std::vector<Vector2> const& rhs);
	float operator*(Vector2& rhs);
	Vector2& operator+=(Vector2 const& rhs);
	Vector2& operator-=(Vector2 const& rhs);
	Vector2& operator/=(float const& rhs);
	float& operator[](int index);
	float operator[](int index) const;
	bool operator==(const Vector2& rhs);
	float dot_product(Vector2 const& rhs) const;
	float max_component();
	float norm() const;
	Vector2 normalize() const;
	float get_x();
	float get_y();
	void set_x(float x);
	void set_y(float y);
	~Vector2();
	friend Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs);
	friend Vector2 operator*(std::vector<Vector2> const& lhs, const Vector2& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
	friend Vector2 operator*(float scalar, Vector2 const& rhs);
	friend Vector2 operator*(Vector2 const& lhs, float scalar);
	friend Vector2 operator/(Vector2 const& lhs, float scalar);
};