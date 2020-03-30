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
	float operator*(Vector4& rhs);
	Vector4 operator+(Vector4& rhs);
	Vector4& operator*(float rhs);
	float& operator[](int index);
	friend std::ostream& operator<<(std::ostream& os, const Vector4& v);
};

