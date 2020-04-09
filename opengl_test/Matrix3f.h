#pragma once

#include <vector>
#include "Vector3.h"
#include "Matrix2f.h"

class Matrix3f
{
public:
	Matrix3f();
	Vector3& operator[](int i);
	Vector3 operator[](int i) const;
	friend Matrix3f operator*(float x, Matrix3f const& m);
	float determinant();
	Matrix2f gl_getCofactorMatrix(unsigned int column, unsigned int row);
private:
	std::vector<Vector3> m_matrix;
};