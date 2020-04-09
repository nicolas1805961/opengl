#include "Vector4.h"

Vector4::Vector4(): x(0), y(0), z(0), w(1)
{}

Vector4::Vector4(float x, float y, float z, float w /*= 1*/): x(x), y(y), z(z), w(w)
{}

Vector4::Vector4(float f): x(f), y(f), z(f), w(f)
{}

float Vector4::operator*(Vector4 const& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

Vector4& Vector4::operator*(float rhs)
{
	Vector4 res;
	res[0] = this->x * rhs;
	res[1] = this->y * rhs;
	res[2] = this->z * rhs;
	res[3] = this->w * rhs;
	return res;
}

Vector4 Vector4::operator+(Vector4& rhs)
{
	Vector4 res;
	res[0] = this->x + rhs.x;
	res[1] = this->y + rhs.y;
	res[2] = this->z + rhs.z;
	res[3] = this->w + rhs.w;
	return res;
}

float Vector4::get_x()
{
	return x;
}

float Vector4::get_y()
{
	return y;
}

float Vector4::get_z()
{
	return z;
}

float Vector4::get_w()
{
	return w;
}

void Vector4::perspectiveDivision()
{
	x /= w;
	y /= w;
	z /= w;
	w /= w;
}

float& Vector4::operator[](int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

float Vector4::operator[](int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

std::ostream& operator<<(std::ostream& os, const Vector4& v)
{
	return os << v.x << " " << v.y << " " << v.z << " " << v.w << "\n";
}