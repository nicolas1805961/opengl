#include "Vector2.h"

Vector2::Vector2() : x(0.0f), y(0.0f)
{}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(float f)
{
	this->x = f;
	this->y = f;
}

Vector2& Vector2::operator/=(float const& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}

Vector2 Vector2::operator*(std::vector<Vector2> const& rhs)
{
	Vector2 res(0);
	res.x = this->x * rhs[0].x + this->y * rhs[0].y;
	res.y = this->x * rhs[1].x + this->y * rhs[1].y;
	return res;
}

float Vector2::operator*(Vector2& rhs)
{
	return x * rhs[0] + y * rhs[1];
}

Vector2& Vector2::operator-=(Vector2 const& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

float Vector2::max_component()
{
	return std::max(this->x, this->y);
}

Vector2 Vector2::operator+(Vector2 const& rhs)
{
	return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2& Vector2::operator+=(Vector2 const& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

float& Vector2::operator[](int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	}
}

float Vector2::operator[](int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	}
}

bool Vector2::operator==(const Vector2& rhs)
{
	if (this->x == rhs.x && this->y == rhs.y)
		return true;
	return false;
}

float Vector2::dot_product(Vector2 const& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::norm() const
{
	return sqrtf(this->dot_product(*this));
}

Vector2 Vector2::normalize() const
{
	Vector2 normalized_vector = (*this) * (1 / norm());
	if (normalized_vector.x < 0.0000001 && normalized_vector.x > -0.0000001)
		normalized_vector.x = 0;
	if (normalized_vector.y < 0.0000001 && normalized_vector.y > -0.0000001)
		normalized_vector.y = 0;
	return normalized_vector;
}

float Vector2::get_x()
{
	return x;
}

float Vector2::get_y()
{
	return y;
}

void Vector2::set_x(float x)
{
	this->x = x;
}

void Vector2::set_y(float y)
{
	this->y = y;
}

Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs)
{
	Vector2 res(0.0f);
	res[0] = lhs.x - rhs.x;
	res[1] = lhs.y - rhs.y;
	return res;
}

Vector2::~Vector2() {}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
	return os << "(" << v.x << ", " << v.y << ")";
}
Vector2 operator*(float scalar, Vector2 const& rhs)
{
	return Vector2(scalar * rhs.x, scalar * rhs.y);
}

Vector2 operator*(Vector2 const& lhs, float scalar)
{
	return Vector2(scalar * lhs.x, scalar * lhs.y);
}

Vector2 operator*(std::vector<Vector2> const& lhs, const Vector2& rhs)
{
	Vector2 res(0);
	res.x = lhs[0].x * rhs.x + lhs[0].y * rhs.y;
	res.y = lhs[1].x * rhs.x + lhs[1].y * rhs.y;
	return res;
}

Vector2 operator/(Vector2 const& lhs, float scalar)
{
	return Vector2(lhs.x / scalar, lhs.y / scalar);
}