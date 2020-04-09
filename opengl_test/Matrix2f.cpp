#include "Matrix2f.h"

Matrix2f::Matrix2f()
{
	m_matrix = std::vector<Vector2>(2, Vector2(0));
}

Vector2& Matrix2f::operator[](int i)
{
	return m_matrix[i];
}

Vector2 Matrix2f::operator[](int i) const
{
	return m_matrix[i];
}

Matrix2f operator*(float x, Matrix2f const& m)
{
	Matrix2f result;
	result[0][0] = m[0][0] * x;
	result[0][1] = m[0][1] * x;
	result[1][0] = m[1][0] * x;
	result[1][1] = m[1][1] * x;
	return result;
}

float Matrix2f::determinant()
{
	return (m_matrix[0][0] * m_matrix[1][1]) - (m_matrix[0][1] * m_matrix[1][0]);
}