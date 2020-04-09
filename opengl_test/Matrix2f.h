#pragma once

#include <vector>
#include "Vector2.h"

class Matrix2f
{
public:
	Matrix2f();
	Vector2& operator[](int i);
	Vector2 operator[](int i) const;
	float determinant();
	friend Matrix2f operator*(float x, Matrix2f const& m);
private:
	std::vector<Vector2> m_matrix;
};
