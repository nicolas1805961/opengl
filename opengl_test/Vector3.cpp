#include "Vector3.h"

Vector3::Vector3(): x(0.0f), y(0.0f), z(0.0f)
{}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(float f)
{
	this->x = f;
	this->y = f;
	this->z = f;
}

Vector3& Vector3::operator/=(float const& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
	return *this;
}

Vector3 Vector3::operator*(std::vector<Vector3> const& rhs)
{
	Vector3 res(0);
	res.x = this->x * rhs[0].x + this->y * rhs[0].y + this->z * rhs[0].z;
	res.y = this->x * rhs[1].x + this->y * rhs[1].y + this->z * rhs[1].z;
	res.z = this->x * rhs[2].x + this->y * rhs[2].y + this->z * rhs[2].z;
	return res;
}

float Vector3::operator*(Vector3& rhs)
{
	return x * rhs[0] + y * rhs[1] + z * rhs[2];
}

Vector3& Vector3::operator-=(Vector3 const& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

float Vector3::max_component()
{
	return std::max(this->x, std::max(this->y, this->z));
}

Vector3 Vector3::operator+(Vector3 const& rhs)
{
	return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

Vector3& Vector3::operator+=(Vector3 const& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3 Vector3::operator+(Vector3 const& rhs) const
{
	return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

float& Vector3::operator[](int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}

float Vector3::operator[](int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}

bool Vector3::operator==(const Vector3& rhs)
{
	if (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z)
		return true;
	return false;
}

void Vector3::perspectiveDivision()
{
	x /= z;
	y /= z;
	z /= z;
}

float Vector3::dot_product(Vector3 const& rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3 Vector3::cross_product(Vector3 const& rhs)
{
	return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float Vector3::norm() const
{
	return sqrtf(this->dot_product(*this));
}

Vector3 Vector3::normalize() const
{
	if (x == 0 && y == 0 && z == 0)
		return *this;
	Vector3 normalized_vector = (*this) * (1 / norm());
	if (normalized_vector.x < 0.0000001 && normalized_vector.x > -0.0000001)
		normalized_vector.x = 0;
	if (normalized_vector.y < 0.0000001 && normalized_vector.y > -0.0000001)
		normalized_vector.y = 0;
	if (normalized_vector.z < 0.0000001 && normalized_vector.z > -0.0000001)
		normalized_vector.z = 0;
	return normalized_vector;
}

float Vector3::get_x()
{
	return x;
}

float Vector3::get_x() const
{
	return x;
}

float Vector3::get_y()
{
	return y;
}

float Vector3::get_y() const
{
	return y;
}

void Vector3::set_x(float x)
{
	this->x = x;
}

void Vector3::set_y(float y)
{
	this->y = y;
}

void Vector3::set_z(float z)
{
	this->z = z;
}

Vector3 operator-(Vector3 const& lhs, Vector3 const& rhs)
{
	Vector3 res(0.0f);
	res[0] = lhs.x - rhs.x;
	res[1] = lhs.y - rhs.y;
	res[2] = lhs.z - rhs.z;
	return res;
}

float Vector3::get_z()
{
	return z;
}

float Vector3::get_z() const
{
	return z;
}

Vector3::~Vector3() {}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
Vector3 operator*(float scalar, Vector3 const& rhs)
{
	return Vector3(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
}

Vector3 operator*(Vector3 const& lhs, float scalar)
{
	return Vector3(scalar * lhs.x, scalar * lhs.y, scalar * lhs.z);
}

Vector3 operator*(std::vector<Vector3> const& lhs, const Vector3& rhs)
{
	Vector3 res(0);
	res.x = lhs[0].x * rhs.x + lhs[0].y * rhs.y + lhs[0].z * rhs.z;
	res.y = lhs[1].x * rhs.x + lhs[1].y * rhs.y + lhs[1].z * rhs.z;
	res.z = lhs[2].x * rhs.x + lhs[2].y * rhs.y + lhs[2].z * rhs.z;
	return res;
}

Vector3 operator/(Vector3 const& lhs, float scalar)
{
	return Vector3(lhs.x / scalar, lhs.y / scalar, lhs.z / scalar);
}