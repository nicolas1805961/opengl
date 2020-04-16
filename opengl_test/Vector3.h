#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

class Vector3
{
private:
	float x;
	float y;
	float z;

public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float f);
	Vector3 operator+(Vector3 const& rhs);
	Vector3 operator+(Vector3 const& rhs) const;
	Vector3 operator*(std::vector<Vector3> const& rhs);
	float operator*(Vector3& rhs);
	Vector3& operator+=(Vector3 const& rhs);
	Vector3& operator-=(Vector3 const& rhs);
	Vector3& operator/=(float const& rhs);
	bool operator<(Vector3 const& right);
	float& operator[](int index);
	float operator[](int index) const;
	bool operator==(const Vector3& rhs);
	void perspectiveDivision();
	float dot_product(Vector3 const& rhs) const;
	float max_component();
	Vector3 cross_product(Vector3 const& rhs);
	float norm() const;
	Vector3 normalize() const;
	float get_x();
	float get_x() const;
	float get_y();
	float get_y() const;
	float get_z();
	float get_z() const;
	void set_x(float x);
	void set_y(float y);
	void set_z(float z);
	~Vector3();
	friend Vector3 operator-(Vector3 const& lhs, Vector3 const& rhs);
	friend Vector3 operator*(std::vector<Vector3> const& lhs, const Vector3& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
	friend Vector3 operator*(float scalar, Vector3 const& rhs);
	friend Vector3 operator*(Vector3 const& lhs, float scalar);
	friend Vector3 operator/(Vector3 const& lhs, float scalar);
};
