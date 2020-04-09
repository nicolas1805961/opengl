#include "Matrix3f.h"

Matrix3f::Matrix3f()
{
	m_matrix = std::vector<Vector3>(3, Vector3(0));
}

Vector3& Matrix3f::operator[](int i)
{
	return m_matrix[i];
}

Vector3 Matrix3f::operator[](int i) const
{
	return m_matrix[i];
}

Matrix3f operator*(float x, Matrix3f const& m)
{
	Matrix3f result;
	result[0][0] = m[0][0] * x;
	result[0][1] = m[0][1] * x;
	result[0][2] = m[0][2] * x;
	result[1][0] = m[1][0] * x;
	result[1][1] = m[1][1] * x;
	result[1][2] = m[1][2] * x;
	result[2][0] = m[2][0] * x;
	result[2][1] = m[2][1] * x;
	result[2][2] = m[2][2] * x;
	return result;
}

Matrix2f Matrix3f::gl_getCofactorMatrix(unsigned int column, unsigned int row)
{
	Matrix2f result;
	unsigned int a = 0, b = 0;
	for (size_t i = 0; i < 3; i++)
	{
		if (i == column)
			continue;
		for (size_t j = 0; j < 3; j++)
		{
			if (j == row)
				continue;
			result[a][b] = m_matrix[i][j];
			b++;

		}
		a++;
		b = 0;
	}
	return result;
}

float Matrix3f::determinant()
{
	float a = m_matrix[0][0] * gl_getCofactorMatrix(0, 0).determinant();
	float b = m_matrix[1][0] * -1 * gl_getCofactorMatrix(1, 0).determinant();
	float c = m_matrix[2][0] * gl_getCofactorMatrix(2, 0).determinant();
	return a + b + c;
}
