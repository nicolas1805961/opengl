#pragma once

#include <iostream>

class Vector4
{
private:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4();
	Vector4(float x, float y, float z, float w = 1);
	Vector4(float f);
	float operator*(Vector4 const& rhs);
	Vector4 operator+(Vector4& rhs);
	float get_x();
	float get_y();
	float get_z();
	float get_w();
	void perspectiveDivision();
	Vector4& operator*(float rhs);
	float& operator[](int index);
	float operator[](int index) const;
	friend std::ostream& operator<<(std::ostream& os, const Vector4& v);
};

