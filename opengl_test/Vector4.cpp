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

Vector3 Vector4::xyz()
{
	Vector3 res(x, y, z);
	return res;
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

Vector4 operator-(Vector4 const& left, Vector4 const& right)
{
	Vector4 res;
	res[0] = left[0] - right[0];
	res[1] = left[1] - right[1];
	res[2] = left[2] - right[2];
	res[3] = left[3] - right[3];
	res.perspectiveDivision();
	return res;
}

Vector4 operator/(Vector4 const& left, float right)
{
	Vector4 res;
	res[0] = left[0] / right;
	res[1] = left[1] / right;
	res[2] = left[2] / right;
	res[3] = left[3] / right;
	res.perspectiveDivision();
	return res;
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